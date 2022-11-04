#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    char *s = getenv("HOME");
    char *f = "log.txt";
    int len = strlen(s) + strlen(f) + 2; // (2 : for '/' and '\0')
    char *filepath = malloc((len+1)*sizeof(*filepath));

    int res = snprintf(filepath, len+1, "%s/%s", s, f);
    FILE *log = fopen(filepath, "a+");

    if(res == len){
        fprintf(log, "Error composing path\n");
    }

    for(int i = 0; i < argc; i++){
        fprintf(log, "argv[%d] = '%s'\n", i, argv[i]);
    }

    fprintf(log, "COMP_LINE = '%s'\n", getenv("COMP_LINE"));
    fprintf(log, "COMP_POINT = '%s'\n", getenv("COMP_POINT"));
    fprintf(log, "COMP_KEY = '%s'\n", getenv("COMP_KEY"));
    fprintf(log, "COMP_TYPE = '%s'\n", getenv("COMP_TYPE"));

    printf("apple\napricot\nbananna\ncherry\n");

    free(filepath);

    return 0;
}
