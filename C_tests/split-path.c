#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Example C code that splits a PATH-like variable on ':' and re-prints
 * the components joined by ':'.
 *
 * We note that the decomposition loop cause an empty component for leading
 * and trailing colons as well as for double colons which is what we want
 * and these empty components have the desired effect of producint leading,
 * trailing, or double colons in the final output.
 */

int main(void){
    char *components[100];
    char *path = getenv("MATH");
    if(path == NULL){
        return 1;
    }
    int i = 0;
    int N;
    char *p = path;
    while(1){
        // Find next non-delim, doesn't preserve leading, trailing, double seps
        // while(*p == ':') p++;
        // if(*p == '\0'){
        //     fprintf(stderr, "break1\n");
        //     break;
        // }

        components[i++] = p;

        // Find next delim
        while(*p != ':' && *p != '\0') p++;
        if(*p == '\0'){
            break;
        } else {
            *p++ = '\0';
        }
    }
    N = i;
    for(int i = 0; i<N; i++){
        fprintf(stderr, "Component[%d] = '%s'\n", i, components[i]);
    }

    /*
     * Method 1: output a separator after every element except the last
     * one which means we have to check inside the if if we are the last
     * one
     */
    fprintf(stderr, "Method 1\n");
    for(int i = 0; i < N; i++){
        fputs(components[i], stdout);
        if( i != N-1 ){
            fputc(':', stdout);
        }
    }
    fputc('\n', stdout);

    /*
     * Method 2: Output the first element separately and then output all the
     * other ones preceeded by a delimiter.  We still need at least one if
     * to ensure we can access components[0].
     */
    fprintf(stderr, "Method 2\n");
    if(N > 0){
        fputs(components[0], stdout);
        for(int i = 1; i<N; i++){
            fprintf(stdout, "%c%s", ':', components[i]);
        }
        fputc('\n', stdout);
    }

    /*
     * Method 3: Same idea as the last one but flipped around, we still need
     * the if to ensure there is at least one component like above.
     */
    fprintf(stderr, "Method 3\n");
    if(N > 0){
        for(int i = 0; i < N-1; i++){
            fprintf(stdout, "%s%c", components[i], ':');
        }
        fputs(components[N-1], stdout);
        fputc('\n', stdout);
    }
}
