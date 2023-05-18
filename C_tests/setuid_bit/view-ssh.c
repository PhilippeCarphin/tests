#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *config_file="/home/phc001/.ssh/config";

    FILE *f = fopen(config_file, "r");
    if(f == NULL){
        perror(config_file);
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
