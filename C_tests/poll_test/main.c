#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*
 * Start of test of POLL system call.
 *
 * This program requires filenames as arguments and calls
 * poll with the list of files as arguments in the form of
 * an array of struct pollfd.
 *
 * The program doesn't do anything meaningful with the result.
 * I just made it because I left myself a note to make a test
 * with this function.
 */
int main(int argc, char **argv){
    struct pollfd poll_fds[argc];
    for(int i = 1; i < argc ; i++){
        struct pollfd *pfd = poll_fds + (i-1);
        pfd->fd = open(argv[i], O_RDONLY);
        pfd->events = (POLLIN);

    }
    int poll_res = poll(poll_fds, argc, 10000);
    fprintf(stderr, "poll_res = %d\n", poll_res);

    return 0;
}
