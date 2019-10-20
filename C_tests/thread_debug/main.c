#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int keep_going = 0;
typedef struct thread_params{
    const char* name;
}thread_params_t;
pthread_mutex_t g_mutex;


void * thread_worker(void *void_star_params)
{
    thread_params_t *params = (thread_params_t *)void_star_params;
    while(keep_going)
    {
        pthread_mutex_lock(&g_mutex);
        printf("My name is '%s'\n", params->name);
        pthread_mutex_unlock(&g_mutex);
    }

    return NULL;
}



int main() {
    pthread_mutex_t * mutex_ptr = &g_mutex;
    pthread_mutex_init(&g_mutex, NULL);
    printf("Hello, World!\n");
    keep_going = 1;

    thread_params_t thp;
    thp.name = "First thread name";

    thread_params_t thp2;
    thp2.name = "Second thread name";

    pthread_mutex_lock(&g_mutex);

    pthread_t my_thread;
    pthread_create(&my_thread, NULL, thread_worker, (void*)&thp);

    pthread_t my_thread2;
    pthread_create(&my_thread2, NULL, thread_worker, (void*)&thp2);

    // pthread_mutex_unlock(&g_mutex);
    // Enough time so that you can hit Resume Program in the debugger a couple times
    // with a breakpoint on the printf in the thread worker
    usleep(400000);
    keep_going = 0;
    pthread_mutex_unlock(&g_mutex);


    pthread_join(my_thread, NULL);
    pthread_join(my_thread2, NULL);
    return 0;
}