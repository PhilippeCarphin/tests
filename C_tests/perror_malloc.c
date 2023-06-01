#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
 * Just a quick test to see if malloc sets errno so that I can do
 * perror("malloc") and get a reason printed.
 *
 * If malloc didn't touch errno, then who knows what perror would
 * print.
 *
 * In this case, it prints "malloc: Could not allocate memory"
 *
 * Because these messages are canned and identified by the int errno
 * and are not composed by the failing function.  So, for example,
 * malloc cannot put the number of requested bytes in the error
 * message.
 *
 * We can however use strerror(errno) to return the string that
 * perror would have printed and use it in a print command with more
 * information.
 */

int main(void){

    size_t s = -1;
    fprintf(stderr, "s = %lu\n", s);
    char *p = malloc(-1);
    if(p == NULL){
        perror("malloc");
        fprintf(stderr, "malloc: %s: %lu\n", strerror(errno), s);
        return 1;
    }

    return 0;
}
