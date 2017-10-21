#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

volatile int done = 0;

void my_signal_handler(int signum)
{
	printf("%s()\n", __FUNCTION__);
	raise(SIGTSTP);
	done = 1;
}

void my_susp_handler(int signum)
{
	printf("%s()\n", __FUNCTION__);
}

void my_kill_handler(int signum)
{
	printf("%s()\n", __FUNCTION__);
}

void my_segfault_handler(int signum)
{
	printf("%s()\n", __FUNCTION__);
}

int main(int argc, char **argv)
{
	signal(SIGINT, my_signal_handler);
	signal(SIGTSTP, my_susp_handler);
	signal(SIGKILL, my_kill_handler);
	signal(SIGSEGV, my_segfault_handler);
	while(!done)
	{
		// wait for signals
	}
	printf("DONE\n");
	int *b = 9000;
	int c = b[8];
	return 0;
}
