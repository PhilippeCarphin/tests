#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){
    char concat[100];
    if(argc <= 2){
        fprintf(stderr, "Not enough arguments %d (need 2)\n", argc-1);
        return 1;
    }

    int snprinf_result = snprintf(concat, 100, "%s/%s", argv[1], argv[2]);
    fprintf(stderr, "snprinf result :%d\n", snprinf_result);

    char decomp_left[100];
    char decomp_right[100];

    int sscanf_result = sscanf(concat, "%[^/]/%[^/]", decomp_left, decomp_right);
    fprintf(stderr, "sscanf_result: %d\n", sscanf_result);
    fprintf(stderr, "decomp_left='%s', decomp_right='%s'\n", decomp_left, decomp_right);
    return (sscanf_result == 2);
}

