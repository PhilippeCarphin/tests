#include <stdlib.h>
#include <stdio.h>

/*
 * This test demonstrates the underscore special environment variable.
 *
 * It seems to be a bash special variable 
 *
   _ At shell startup, set to the absolute pathname used to invoke the  shell  or  shell
     script being executed as passed in the environment or argument list.  Subsequently,
     expands to the last argument to the previous command, after expansion.  Also set to
     the  full  pathname  used  to  invoke  each  command  executed  and  placed  in the
     environment exported to that command.  When checking mail, this parameter holds the
     name of the mail file currently being checked.
 */

int main(void){

    char *underscore = getenv("_");
    if(underscore == NULL){
        printf("There is no underscore environement variable\n");
    } else {
        printf("The value of underscore is '%s'\n", underscore);
    }
    return 0;
}

