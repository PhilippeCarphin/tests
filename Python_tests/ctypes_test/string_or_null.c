#include <stdlib.h>
#include <stdio.h>

int string_or_null(char *s){
    if(s == NULL){
        fprintf(stdout, "The string is NULL\n");
    } else {
        fprintf(stdout, "The string is '%s'\n", s);
    }
    return 0;
}

