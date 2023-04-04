#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void){
    int s = socket(AF_UNIX, SOCK_STREAM, 0);
    if(s == -1){
        fprintf(stderr, "Failed to create socket fd\n");
        exit(1);
    }
    struct sockaddr_un server;
    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, "/tmp/foo", sizeof(server.sun_path));

    int err = connect(
        s,
        (struct sockaddr *)&server,
        sizeof(struct sockaddr_un)
    );
    if(err == -1){
        exit(1);
    }

    int num_read;
    const int BUF_SIZE = 10;
    char buf[BUF_SIZE];
    while((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0 ) {
        if(write(s, buf, num_read) != num_read){
            fprintf(stderr, "Failed/partial write\n");
            break;
        }
    }
}
