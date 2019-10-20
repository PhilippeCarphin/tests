#include <stdio.h>
#include <unistd.h>
int g_variable_int = 0;
int subprocess_keeps_going = 1;

void task_of_subprocess(){
    while(subprocess_keeps_going)
        printf("subprocess g_variable_int=%d\n", g_variable_int);
}



int main() {

    int fork_ret_val = fork();
    printf("Hello, World! fork_ret_val=%d\n", fork_ret_val);

    if(fork_ret_val == 0){
        printf("I am the parent process\n");
        // 
    } else {
        printf("I am the child process\n");
        task_of_subprocess();
    }



    return 0;
}