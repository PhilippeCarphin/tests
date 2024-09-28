#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    char *s = getenv("HOME");
    char *f = ".log.txt";
    int len = strlen(s) + strlen(f) + 2; // (2 : for '/' and '\0')
    char *filepath = malloc((len+1)*sizeof(*filepath));

    int res = snprintf(filepath, len+1, "%s/%s", s, f);
    FILE *log = fopen(filepath, "a+");

    if(res == len){
        fprintf(log, "Error composing path\n");
    }

    fprintf(log, "==========================================================\n");
    for(int i = 0; i < argc; i++){
        fprintf(log, "argv[%d] = '%s'\n", i, argv[i]);
    }
    const char *cur = argv[2];

    fprintf(log, "COMP_LINE = '%s'\n", getenv("COMP_LINE"));
    fprintf(log, "COMP_POINT = '%s'\n", getenv("COMP_POINT"));

    int key;
    char *comp_key = getenv("COMP_KEY");
    if(comp_key == NULL){
        fprintf(log, "ERROR: Environment variable COMP_KEY is missing\n");
        return 1;
    }
    sscanf(comp_key, "%d", &key);
    fprintf(log, "COMP_KEY = '%c' (%d)\n", key, key);

    int type;
    char *comp_type = getenv("COMP_KEY");
    if(comp_type == NULL){
        fprintf(log, "ERROR: Environment variable COMP_TYPE is missing\n");
        return 1;
    }
    sscanf(comp_type, "%d", &type);
    fprintf(log, "COMP_TYPE = '%c' (%d)\n", type, type);

    const char *candidates[] = {"apple", "apricot", "bananna", "cherry"};
    size_t nb_candidates = sizeof(candidates) / sizeof(*candidates);
    size_t len_cur = strlen(cur);
    for(const char **c = candidates; c < candidates + nb_candidates; c++){
        if(strncmp(*c, argv[2], len_cur) == 0){
            fprintf(log, "Candidate %s matches cur %s\n", *c, cur);
            printf("%s\n", *c);
        }
    }

    free(filepath);

    return 0;
}
