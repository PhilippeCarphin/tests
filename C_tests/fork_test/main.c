#include <stdio.h>
#include <unistd.h>

void task_of_subprocess(){
    while(1) {
        printf("subprocess");
    }
}

int main() {

    int fork_ret_val = fork();
    printf("Hello, World! fork_ret_val=%d\n", fork_ret_val);
    return 0;
}