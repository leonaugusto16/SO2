#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/dir.h>
#include <dirent.h>
#include "rm.h"

static char** s_argv;

int rmrf(const char *name, const struct stat *status, int type, struct FTW *ftwbuf) {
  int rv = remove(name);
  return rv;
}

int rm(char *name) {
  struct stat sb;
  char *file;

  if(stat(name,&sb)==-1){
    perror("stat");
    return 1;
  }
  
  switch(sb.st_mode & S_IFMT){
    case S_IFDIR: printf("rm: cannot remove: Is a directory\n");
    default:
      unlink(name);
  }
  return 0;
}

int rmd(const char *name, const struct stat *status, int type, struct FTW *ftwbuf) {
  DIR* mydir=opendir(s_argv[1]);
  struct dirent *myfile;
  int count=0;
  if(type == FTW_DP){
    if(mydir==NULL){
      int rv = remove(name);
      return rv;
    }
  }
  else{
    printf("rm: cannot remove: Directory not empty\n",name);
  }
  return 1;
}

int main(int argc, char *argv[]) {
 int flags = FTW_DEPTH | FTW_PHYS;
 int caso;
 s_argv = argv;
 caso = getopt(argc, argv,"rdh");

 if(argc == 1)
  printf("rm: missing operand\n");
 else{
  switch(caso){
    case 'r':
      if(nftw(argv[2], rmrf, 64, flags)==-1){
        perror("myrm");
      }break;
    case 'd':
      if(nftw(argv[2],rmd ,64, flags)==-1){
        perror("myrm");
      }break;
    case 'h':
      printf("Help: Para remover arquivos, use ./rm -r caminho_do_arquivo. Se for utilizado ./rm caminho_do_arquivo, ele também é excluído (default). Para remover diretórios use ./rm -d caminho_do_diretorio.\n");
      break;

    default:
      rm(argv[1]);
      break;
  }    
 }
 return 0;
}
