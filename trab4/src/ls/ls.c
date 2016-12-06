#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include "ls.h"

static char perms_buff[30];
typedef enum { false, true } bool;

const char *get_perms(mode_t mode){
  char ftype = '?';

  if (S_ISREG(mode)) ftype = '-';
  if (S_ISLNK(mode)) ftype = 'l';
  if (S_ISDIR(mode)) ftype = 'd';
  if (S_ISBLK(mode)) ftype = 'b';
  if (S_ISCHR(mode)) ftype = 'c';
  if (S_ISFIFO(mode)) ftype = '|';

  sprintf(perms_buff, "%c%c%c%c%c%c%c%c%c%c %c%c%c", ftype,
  mode & S_IRUSR ? 'r' : '-',
  mode & S_IWUSR ? 'w' : '-',
  mode & S_IXUSR ? 'x' : '-',
  mode & S_IRGRP ? 'r' : '-',
  mode & S_IWGRP ? 'w' : '-',
  mode & S_IXGRP ? 'x' : '-',
  mode & S_IROTH ? 'r' : '-',
  mode & S_IWOTH ? 'w' : '-',
  mode & S_IXOTH ? 'x' : '-',
  mode & S_ISUID ? 'U' : '-',
  mode & S_ISGID ? 'G' : '-',
  mode & S_ISVTX ? 'S' : '-');

  return (const char *)perms_buff;
}

int is_hidden(const char *name)
{
  if(name[0] == '.' || strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
  return 1;
  else return 0;
}



void lsl(struct dirent *myfile){
  struct stat mystat;
  int count=0;

  char datestring[256];
  struct passwd pwent;
  struct passwd *pwentp;
  struct group grp;
  struct group *grpt;
  struct tm time;
  char buf[1024];


  stat(myfile->d_name, &mystat);
  printf("%10.10s", get_perms(mystat.st_mode));
  printf(" %d", mystat.st_nlink);

  if (!getpwuid_r(mystat.st_uid, &pwent, buf, sizeof(buf), &pwentp)){
    printf(" %s", pwent.pw_name);
  }
  else{
    printf(" %d", mystat.st_uid);
  }

  if (!getgrgid_r (mystat.st_gid, &grp, buf, sizeof(buf), &grpt)){
    printf(" %s", grp.gr_name);
  }
  else{
    printf(" %d", mystat.st_gid);
  }

  printf(" %5d", (int)mystat.st_size);

  localtime_r(&mystat.st_mtime, &time);
  strftime(datestring, sizeof(datestring), "%b %d %H:%M", &time);

  printf(" %s %s\n", datestring, myfile->d_name);

}

void ls(DIR* mydir,bool flaga, bool flagl){
  struct dirent *myfile;
  int count;

  if(flaga == false && flagl == false){
    while((myfile = readdir(mydir)) != NULL){
      if(!is_hidden(myfile->d_name)){
        printf(" %s ", myfile->d_name);
      }
    }
    printf("\n");
  }

  else if(flaga == true && flagl == false){
    while((myfile = readdir(mydir)) != NULL){
        printf(" %s ", myfile->d_name);
    }
    printf("\n");
  }

  else if(flaga == false && flagl == true){
    while((myfile = readdir(mydir)) != NULL){
      if(!is_hidden(myfile->d_name)){  
        lsl(myfile);
        count++;
      }
    }
    printf("total %d\n", count);
  }

  else if(flaga == true && flagl == true){
    while((myfile = readdir(mydir)) != NULL){
        lsl(myfile);
        count++;
    }
    printf("total %d\n", count);
  }
}

int main(int argc, char* argv[])
{
    DIR *mydir;
    int caso;
    char *path; 
    bool flaga=false,flagl=false;
    int optind=0;

    path = argv[argc-1];
    while(optind < argc) {
      if((caso = getopt(argc, argv, "lah")) != -1) {
        switch(caso){
          case 'a':
            if(strcmp(path,"-a") == 0 || strcmp(path,"-l") == 0 ){
              path = ".";
              flaga=true;
            }
            else{
              flaga=true;
            }
            break;
          case 'l':
            if(strcmp(path,"-a") == 0 || strcmp(path,"-l") == 0){
              path = ".";
              flagl=true;
            } 
            else{
              flagl=true;
            } 
            break;
          case 'h':
              printf("Help: Para apenas listar os arquivos, use ./ls -a. Se deseja ver informações completas, use ./ls -l\n");exit(0);
              break;   
        }
      } else if(argc ==1) path = ".";
      optind++;
    }
    mydir = opendir(path);
    ls(mydir,flaga,flagl);
    
    closedir(mydir);
 }
