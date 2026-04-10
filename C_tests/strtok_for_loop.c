#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    if(argc < 2){
        fprintf(stderr, "%s: ERROR: Not enough arguments: %d\n", argv[0], argc);
        return 1;
    }
    char *s = strdup(argv[1]);
    char *tmp;
    for(char *tok = strtok_r(s,",", &tmp); tok != NULL; tok = strtok_r(NULL, ",", &tmp)){
        fprintf(stderr, "tok = '%s'\n", tok);
    }
    return 0;
}
