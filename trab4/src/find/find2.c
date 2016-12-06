#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "find.h"
#include <getopt.h>

static int    s_argc;
static char** s_argv;

static int
display_info(const char *fpath, const struct stat *sb,
             int tflag, struct FTW *ftwbuf){
    int matched = 0, i;
    for (i=1; i<s_argc; i++){
        const char* match = strstr(fpath, s_argv[i]);
        matched |= (match && *match
                && (strlen(match) == strlen(s_argv[i]))           
                && ((match == s_argv[i]) || (match[-1] == '/')));
    }

    if (matched){
        printf("%s\n",

                fpath);
    }

    return 0;
}

int main(int argc, char *argv[]){
    int caso;
    s_argc = argc-1;
    s_argv = argv+1;
    int flags = FTW_DEPTH | FTW_PHYS;
    
    static struct option long_options[] = {
      {"name", required_argument,0, 'n'},
      {"help", no_argument,0, 'h'},
      {0, 0, 0, 0}
    };
    int option_index = 0;
    caso = getopt_long(argc, argv,"nh",long_options,&option_index);
    switch(caso){
        case 'h':
            printf("Help: Exemplo de uso - ./myfind / teste.txt --> procura em todo / arquivos teste.txt\n");
            break;
        case 'n':
            if (nftw(argv[1], display_info, 20, flags) == -1){
                perror("find");
                exit(EXIT_FAILURE);
            }
    }
    exit(EXIT_SUCCESS);
}
