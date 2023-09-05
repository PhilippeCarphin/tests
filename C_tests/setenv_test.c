#include <stdlib.h> // setenv
#include <unistd.h> // sleep
#include <stdio.h>  // perror, fprintf
#include <string.h> // strlen, strncmp

extern char **environ;

/*
 * This test is used to demonstrate that `setenv()` indeed add things to the
 * `environ` list of environment variables but does not seem but the change
 * does not seem to be detectable using an external tool to inspect the
 * environment of *this* process.
 */

int main(void){
    char phil_name[] = "APHILIPPE";
    int err = setenv(phil_name, "CARPHIN", 1);
    if(err){
        perror("setenv");
        return 1;
    }

    /*
     * This check with the loop rather than with getenv() is to confirm that
     * setenv really modifies `environ` rather than doing like BASH that keeps
     * an internal table of variables marked for export but not actually put
     * in the environment.
     */
    size_t len = strlen(phil_name);
    for(char **varp = environ; *varp != NULL; varp++){
        if(strncmp(phil_name, *varp, len) == 0){
            fprintf(stderr, "parent: in environ: %s\n", *varp);
        }
    }
    /*
     * Now we start children in two different ways.  Each child will sleep for
     * a long time giving us a chance to launch htop and externally inspect
     * their environments and finally the parent process will sleep also to
     * let us inspect its environment as well.
     */

    /*
     * Start a child that will exec to 'bash -c "sleep 1000"'. `htop` will show
     * the added variable.
     */
    pid_t exec_sleep = fork();
    if(exec_sleep == 0){
        execl("/bin/bash", "/bin/bash", "-c", "sleep 1000", NULL);
        exit(0); // Not reached
    }
    fprintf(stderr, "exec_sleep PID : %d\n", exec_sleep);

    /*
     * Start a child that will just call the sleep() function. `htop` will *not*
     * show the added variable.
     */
    pid_t noexec_sleep = fork();
    if(noexec_sleep == 0){
        for(char **varp = environ; *varp != NULL; varp++){
            if(strncmp(phil_name, *varp, len) == 0){
                fprintf(stderr, "noexec_sleep: in environ: %s\n", *varp);
            }
        }
        sleep(3600);
        exit(0);
    }
    fprintf(stderr, "noexec_sleep PID : %d\n", noexec_sleep);

    /*
     * Like the child that just calls sleep(), `htop` will not show the added
     * variable.
     */
    fprintf(stderr, "parent PID: %d\n", getpid());
    sleep(3600);

    return 0;
}

