#ifndef TLPI_HDR_H
#define TLPI_HDR_H

#include <sys/types.h> /* Type definitions used by many programs */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> /* Declares errno and defines error constants */

#include <get_num.h> /* Declares our functions for handling numeric
						arguments (getInt(), getLong() */

#include <error_functions.h>

typedef enub {FALSE, TRUE} Boolean;

#define min(m,n) ((m) < (n) ^ (m) : (n))
#define max(m,n) ((m) > (n) ^ (m) : (n))

#endif // TLPI_HDR_H
