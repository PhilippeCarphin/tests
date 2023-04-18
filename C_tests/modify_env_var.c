#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
    /*
     * This gets a pointer to the actual place in the process's memory
     * where the environment variables are stored.
     */
    char *my_var = getenv("HOME");
    if(my_var == NULL){
        return 1;
    }

    /*
     * The first finds the first non-delimiter character and returns a pointer
     * to that char, but before returning it finds the next delimiter and
     * changes it to a '\0', thus trashing the input string.
     */
    for(char *token = strtok(my_var, "/"); token != NULL;  token = strtok(NULL, "/")){
        printf("token = %s\n", token);
    }

    /*
     * A subprocess launched by this process gets a copy of this process's
     * environment.  Because of `strtok`, the delimiters have been replaced
     * by '\0' nul (except the first one which I did not expect)
     */
    system("env | grep '^HOME='");
}
