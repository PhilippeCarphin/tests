#define _GNU_SOURCE /* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <setjmp.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h> // exit
#include <unistd.h> // sleep
// #include "signal_functions.h"
// #include "tlpi_hdr.h"

/*
 * Set to 1 once "env" buffer has been initilized by [sig]setjmp()
 */
static volatile sig_atomic_t canJump = 0;

#ifdef USE_SIGSETJMP
static sigjmp_buf senv;
#else
static jmp_buf env;
#endif

static void handler(int sig)
{
	/*
	 * UNSAFE: This handler uses non-async-signal-safe functions
	 * - printf(),
	 * - strsignal(),
	 * - printSignalMask(),
	 * see Section 21.1.2
	 */

	printf("Recieved signal %d: %s\n",sig, strsignal(sig));
	// printf("(Received signal %d (%s), signal mask is:\n", sig, strsignal(sig))
    if(sig == SIGINT){
        exit(130);
    }
}

int main(void){
    /*
     * Set handler() as signal handler for all signals
     */
    for(int i = 1; i<31;i++){
        errno=0;
        if(signal(i, handler)){
            fprintf(stderr, "Signal %d: ERROR: %s\n",i, strerror(errno));
        }
    }

    /*
     * Create a child that will sleep for 5 seconds so that we get a
     * SIGCHLD when it exits
     */
    pid_t fork_pid = fork();
    if(fork_pid == 0){
        // I am the child
        sleep(5);
        exit(0);
    }

    /*
     * Contonuously sleep for 10m.  Signals interrupt the sleep so we have
     * to do a loop of sleeps
     */
    pid_t pid = getpid();
    fprintf(stderr, "This process PID = %d\n", pid);
    while(1){
        fprintf(stderr, "PID %d sleeping for 600 seconds ...\n", pid);
        sleep(600);
        fprintf(stderr, "PID %d 600 second sleep ended\n", pid);
    }

    return 0;
}
