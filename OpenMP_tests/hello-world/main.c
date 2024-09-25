#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(void){
    int n = 1000;
    int nb_threads;
    int sum = 0;
    #pragma omp parallel for
    for(int i = 0; i < n; i++){
        int t = omp_get_thread_num();
        if(i == 0){
            // This needs to be inside an omp thing otherwise the function
            // just returns 1
            nb_threads = omp_get_num_threads();
        }
        // #pragma omp atomic
        sum += i;
        fprintf(stderr, "t: %d : This is iteration %d\n", t, i);
    }
    fprintf(stderr, "Number of threads = %d\n", nb_threads);
    fprintf(stderr, "Sum = %d\n", sum);
    return 0;
}
