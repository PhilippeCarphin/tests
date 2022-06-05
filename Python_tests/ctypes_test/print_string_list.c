#include <stdio.h>

int print_string_list(int argc, char **string_list){
    printf("%s() received %d strings:\n", __func__, argc);
    for(int i = 0; i < argc; i++){
        printf("\tstring_list[%d] = %s\n", i, string_list[i]);
    }
    return 42;
}
