#include <stdlib.h> // setenv
#include <unistd.h> // sleep
#include <stdio.h>  // perror, fprintf
#include <string.h> // strlen, strncmp

extern char **environ;

int main(void){
    int err = setenv("APHILIPPE", "CARPHIN", 1);
    if(err){
        perror("setenv");
        return 1;
    }

    fprintf(stderr, "HELLO\n");
    char phil_name[] = "PHILIPPE";
    size_t len = strlen(phil_name);
    pid_t pid = fork();
    if(pid == 0){
        // child
        for(char **varp = environ; *varp != NULL; varp++){
            if(strncmp(phil_name, *varp, len) == 0){
                fprintf(stderr, "child: in environ: %s\n", *varp);
            }
        }
        execl("/bin/bash", "/bin/bash", "-i", NULL);
    } else {
        // parent
        for(char **varp = environ; *varp != NULL; varp++){
            if(strncmp(phil_name, *varp, len) == 0){
                fprintf(stderr, "parent: in environ: %s\n", *varp);
            }
        }
        sleep(3600);
    }

    return 0;
}

