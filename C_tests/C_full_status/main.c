#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid = 0;
void siging_handler(int signum){
    fprintf(stderr, "%s(): signum=%d\n", __func__, signum);
    kill(pid, signum);
}

int main(int argc, char **argv){

    if(argc < 2){
        fprintf(stderr, "%s: ERROR: Not enough arguments: %d\n", argv[0], argc);
        return 1;
    }
    pid = fork();
    if(pid == 0){
        char *prog = argv[1];
        execvp(argv[1], argv+2);
    }


    // PARENT
    int stat_loc;
    int options = 0;
    close(STDIN_FILENO);
    signal(SIGINT, siging_handler);
    int exit_status = waitpid(pid, &stat_loc, options);

    fprintf(stderr, "waitpid(%d,...) returned %d, stat_loc=%d\n", pid, exit_status, stat_loc);
    if(WIFEXITED(stat_loc)){
        fprintf(stderr, "Process has terminated normally by a call to _exit(2) or exit(3)\n");
        fprintf(stderr, "WEXITSTATUS(%d)=%d\n", stat_loc, WEXITSTATUS(stat_loc));
    }

    if(WIFSIGNALED(stat_loc)){
        fprintf(stderr, "Process has terminated due to the receipt of a signal\n");
        fprintf(stderr, "WTERMSIG(%d)=%d\n", stat_loc, WTERMSIG(stat_loc));
    }

    if(WIFSTOPPED(stat_loc)){
        fprintf(stderr, "Process has stopped due to the receipt of a signal\n");
        fprintf(stderr, "WSTOPSIG(%d)=%d\n", stat_loc, WSTOPSIG(stat_loc));
    }
    return 0;
}

