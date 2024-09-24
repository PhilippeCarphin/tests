#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *config_dir="/home/phc001/.ssh";
    if(argc != 2){
        fprintf(stderr, "Must supply an argument 'config' or 'id_rsa.pub'\n");
        exit(1);
    }
    char filepath[1024];
    if(strncmp("config", argv[1], 10) == 0){
        snprintf(filepath, sizeof(filepath), "%s/config", config_dir);
    } else if (strncmp("id_rsa.pub", argv[1], 10) == 0) {
        snprintf(filepath, sizeof(filepath), "%s/id_rsa.pub", config_dir);
    } else {
        fprintf(stderr, "Invalid argument: %s.  Must be either 'config' or 'id_rsa.pub'\n", argv[1]);
        exit(1);
    }

    FILE *f = fopen(filepath, "r");
    if(f == NULL){
        perror(filepath);
        return 1;
    }

    fprintf(stderr, "Successfully opened file!\n");
    char buf[128];
    while(fgets(buf, sizeof(buf), f) != NULL){
        for(char *p = buf; *p != '\0' ; p++){
            char c = *p;
            switch(c){
                case ' ':
                case '\n':
                case '\t':
                    putc(c, stdout);
                    break;
                default:
                    putc('%', stdout);
                    break;
            }
        }
    }

    return 0;
}
