#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

volatile int done = 0;

/*
 * Compile with -D_VOLATILE_ and do CTRL-Z and then CTRL-C
 *
 * then compile without the -D_VOLATILE_ and notice that
 * this changes the behavior of the program.
 *
 * Both times, compilation needs to be done with -O3 so that
 * the compiler optimizes out the while(loop_var) loop in
 * the non-volatile case
 */

#ifdef _VOLATILE_
volatile int loop_var = 0;
#else
int loop_var = 0;
#endif

void my_sigint_handler(int signum)
{
	printf("%s() setting done to 1\n", __FUNCTION__);
	done = 1;
}

void my_susp_handler(int signum)
{
	printf("%s() setting loop_var to 1\n", __FUNCTION__);
	loop_var = 1;
}

void my_kill_handler(int signum)
{
	printf("%s()\n", __FUNCTION__);
}

void my_segfault_handler(int signum)
{
	printf("%s()\n", __FUNCTION__);
	exit(10);
}

int main(int argc, char **argv)
{
	signal(SIGINT, my_sigint_handler);
	signal(SIGTSTP, my_susp_handler);
	signal(SIGKILL, my_kill_handler);
	signal(SIGSEGV, my_segfault_handler);
	loop_var = 0;
	while(!done)
	{
		/*
		 * wait for signals
		 * Pressing CTRL-Z here will set loop_var to 1
		 * Pressing CTRL-C here will set done to 1 and make us exit
		 * the loop.
		 */
	}

	/*
	 * If we compile with optimization, this loop may be optimized out
	 * since the compiler knows that loop_var was set to 0 and not changed
	 * before we enter the loop (except that it might be changed in a signal
	 * handler.
	 */
	while(loop_var){
		printf("Inside the loop that may be optimized out\n");
		break;
	}

	printf("DONE\n");
	int *b = 9000;
	int c = b[8];
	return 0;
}
