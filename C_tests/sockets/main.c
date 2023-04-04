#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void * handle_connection(void* conn){
    long int int_conn = (long int) conn;
    int num_read;
    const int BUF_SIZE=10;
    char buf[BUF_SIZE];
    while((num_read = read(int_conn, buf, BUF_SIZE)) > 0) {
        if(write(STDOUT_FILENO, buf, num_read) != num_read){
            fprintf(stderr, "Failed/partial write\n");
            break;
        }
    }
    return NULL;
}


int main(void){
    int s = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr;
    // memset(&addr,0,sizeof(addr));
    addr.sun_family = AF_UNIX;
    remove("/tmp/foo");
    strncpy(addr.sun_path,"/tmp/foo", sizeof(addr.sun_path));
    int err = bind(
        s,
        (const struct sockaddr*) &addr,
        strlen(addr.sun_path) + 1 + sizeof(addr.sun_family)
    );
    if(err){
        perror("Bind s");
        exit(1);
    }

    err = listen(s, 0);
    if(err) {
        perror("Error during listen");
        exit(1);
    }

    for(;;){
        fprintf(stderr, "for loop\n");
        long int conn = accept(s, NULL, NULL);
        fprintf(stderr, "Accepted connection : %ld\n", conn);
        pthread_t handle;
        int err = pthread_create(&handle, NULL, handle_connection, (void*)conn);
        if(err){
            fprintf(stderr, "Error creating thread\n");
        }
    }

    close(s);
    remove("/tmp/foo");
}
