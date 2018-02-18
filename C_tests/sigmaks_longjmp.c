#define _GNU_SOURCE /* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <stejmp.h>
#include <signal.h>
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

	printf("Recieved signal %d\n");
	// printf("(Received signal %d (%s), signal mask is:\n", sig, strsignal(sig))
