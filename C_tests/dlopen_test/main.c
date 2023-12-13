#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <linux/limits.h>
#include "plugin_interface.h"

int main(int argc, char **argv)
{
    if(argc < 2){
        fprintf(stderr, "ERROR: Must provide an argument\n");
        return 1;
    }

    /*
     * Input data for mean function
     */
    float array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    size_t nb_elem = sizeof(array)/sizeof(*array);

    /*
     * Compose path of plugin file
     */
    const char plugin_dir[] = ".";
    char file_path[PATH_MAX];
    snprintf(file_path, PATH_MAX, "%s/%s.so", plugin_dir, argv[1]);


    /*
     * Use dlopen to load shared library
     */
    void *mean_plugin = dlopen(file_path, RTLD_NOW);
    if(mean_plugin == NULL){
        fprintf(stderr, "ERROR: '%s'\n", dlerror());
        return 1;
    }

    /*
     * Expect it to contain a symbol named "mean" and load this symbol
     * as a MeanFunc (float mean(float *array, nb_elem))
     */
    MeanFunc mean_func = dlsym(mean_plugin, "mean");
    if(mean_func == NULL){
        fprintf(stderr, "ERROR: '%s'\n", dlerror());
        return 1;
    }

    printf("%s is %f\n", argv[1], mean_func(array, nb_elem));

    return 0;
}
