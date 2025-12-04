#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(int argc, char **argv){

    if(argc == 2){
        int nb_threads;
        if(sscanf(argv[1], "%d", &nb_threads) != 1){
            fprintf(stderr, "%s: ERROR: Could not convert argument 1 '%s' to integer\n", argv[0], argv[1]);
            return 1;
        }
        fprintf(stderr, "Setting number of threads to %d\n", nb_threads);
        omp_set_num_threads(nb_threads);
    }

    int num_threads;
    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
    }

    fprintf(stderr, "Number of threads: %d\n", num_threads);

    int i;
    #pragma omp parallel for private(i) shared(num_threads)
    for (i = 0; i < 8; i++) {
        printf("Hello from thread %d, iteration %d out of %d threads.\n", omp_get_thread_num(), i, num_threads);
        sleep(1);
    }

    return 0;
}
