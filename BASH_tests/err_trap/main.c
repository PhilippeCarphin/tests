#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv){

    FILE *f = fopen(argv[1], "w");
    if(f == NULL){
        char buf[1024];
        void * result = strerror_r(errno, buf, 1024);
        fprintf(stderr, "result=%p, result=%d, str=%s\n", result, result, buf);
        return 1;
    }
    fclose(f);
}
