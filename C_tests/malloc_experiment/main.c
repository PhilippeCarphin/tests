#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * In glibc:malloc/malloc.c, there is a diagram that explains that the size
 * of a chunk is stored in the memory preceding pointer returned by malloc()
 * and the size of the next chunk is stored after the chunk.
 *
 * This code does some mallocs and stores one of the returned pointers in 'x'.
 *
 * We get the size of the chunk by looking at the size_t at 'x - sizeof(size_t)'
 * which we lazily assume is 8.
 *
 * We also get the size of the next chunk by looking at 'x + <size passed to malloc>'
 *
    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |             Size of previous chunk, if unallocated (P clear)  |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |             Size of chunk, in bytes                     |A|M|P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |             User data starts here...                          .
        .                                                               .
        .             (malloc_usable_size() bytes)                      .
        .                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |             (size of chunk, but used for application data)    |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |             Size of next chunk, in bytes                |A|0|1|
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */

int main(int argc, char **argv){


    size_t x_alloc_sz;
    if( argc == 1){
        x_alloc_sz = 600;
    } else {
        x_alloc_sz = atoi(argv[1]);
    }

    /*
     * The size of the chunk is always different than the size passed to
     * malloc but not always by the same amount.
     *
     * Print some modulo 8 and 4 just to see if we can discern a pattern
     */
    fprintf(stderr, "x_alloc_sz = %lu\n", x_alloc_sz);
    fprintf(stderr, "x_alloc_sz%%8 = %lu\n", x_alloc_sz%8);
    fprintf(stderr, "x_alloc_sz%%4 = %lu\n", x_alloc_sz%4);

    /*
     * Allocate x after doing some mallocs, and before some more mallocs so
     * that we have previous and next chunks
     */
    char *y = malloc(800);
    char *x = malloc(x_alloc_sz);
    char *z = malloc(900);
    char *w = malloc(1000);
    char *u = malloc(1100);

    /*
     * Get the chunk size by looking at the 8 bytes preceding x
     */
    size_t sz = *(size_t*)(x-8);
    fprintf(stderr, "size of chunk = %lu\n", sz);

    /*
     * Size of previous chunk by looking at the 8 bytes before that
     */
    size_t sz_prev = *(size_t*)(x-16);
    fprintf(stderr, "size of previous chunk = %lu\n", sz_prev);

    /*
     * Size of next chunk but used for application data
     */
    size_t sz_app = *(size_t*)(x+x_alloc_sz);
    fprintf(stderr, "size of chunk (app data): = %lu\n", sz_app);

    /*
     * Size of next chunk
     */
    size_t sz_next = *(size_t*)(x+x_alloc_sz+8);
    fprintf(stderr, "size of next chunk = %lu\n", sz_next);

    fprintf(stderr, "===========================================================\n\n");

    return 0;
}
