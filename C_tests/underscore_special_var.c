#include <stdlib.h>
#include <stdio.h>

int main(void){

    char *underscore = getenv("_");
    if(underscore == NULL){
        printf("There is no underscore environement variable\n");
    } else {
        printf("The value of underscore is '%s'\n", underscore);
    }
    return 0;
}

