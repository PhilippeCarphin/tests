#include <stdio.h>
#include <unistd.h>

void task_of_subprocess(){
    while(1) {
        printf("subprocess");
    }
}

int main() {

    fork();
    printf("Hello, World!\n");
    return 0;
}