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

	printf("%s():%d: Recieved signal %d: %s\n", __func__, __LINE__,sig, strsignal(sig));
	// printf("(Received signal %d (%s), signal mask is:\n", sig, strsignal(sig))
    if(sig == SIGINT){
        exit(130);
    }
}

void print_sig_set(sigset_t * sigset, const char *prefix){

    int empty = 1;
    for(int sig = 1; sig < NSIG; sig++){
        if(sigismember(sigset, sig)){
            empty = 0;
            fprintf(stderr, "%s():%d: %s%d(%s)\n", __func__, __LINE__, prefix, sig, strsignal(sig));
        }
    }
    if(empty){
        fprintf(stderr, "%s():%d: %sis empty set\n",__func__, __LINE__, prefix);
    }

}

int main(void){

    /*
     * Set handler() as signal handler for all signals
     */
    for(int i = 1; i<31;i++){
        errno=0;
        if(signal(i, handler)){
            fprintf(stderr, "%s():%d: Signal %d: ERROR: %s\n",__func__, __LINE__, i, strerror(errno));
        }
    }

    // int sigprocmask (int how, const sigset_t *restrict set, sigset_t *restrict oldset
    sigset_t block_set;
    sigset_t unblock_set;
    sigset_t set;
    sigemptyset(&set);
    sigemptyset(&block_set);
    sigemptyset(&unblock_set);
    sigaddset(&set, SIGWINCH);
    if(sigprocmask(SIG_BLOCK, NULL, &block_set)){
        perror("sigprocmask");
    }
    if(sigprocmask(SIG_UNBLOCK, NULL, &unblock_set)){
        perror("sigprocmask");
    }
    print_sig_set(&block_set, "block_set ");
    print_sig_set(&unblock_set, "unblock_set ");
    for(int i = 1; i<30;i++){
        errno=0;
        fprintf(stderr, "%s():%d: signal %d(%s)",__func__, __LINE__, i, strsignal(i));
        if(sigismember (&block_set, i)){
            fprintf(stderr, " BLOCKED)");
        }
        if(sigismember(&unblock_set, i)){
            fprintf(stderr, " UNBLOCKED)");
        }
        fprintf(stderr, "\n");
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
    fprintf(stderr, "%s():%d: This process PID = %d\n",__func__, __LINE__, pid);
    while(1){
        fprintf(stderr, "%s():%d: PID %d sleeping for 600 seconds ...\n", __func__, __LINE__, pid);
        sleep(600);
        fprintf(stderr, "%s():%d: PID %d 600 second sleep ended\n", __func__, __LINE__, pid);
    }

    return 0;
}
