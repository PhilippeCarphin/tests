#include <stdio.h>
#define _GNU_SOURCE
#include <fnmatch.h>

int main(int argc, char **argv)
{
    if(argc < 3){
        fprintf(stderr, "ERROR: Require at least two arguments\n");
        return 1;
    }

    const char *pattern = argv[1];
    fprintf(stderr, "Pattern is '%s'\n", pattern);

    for(int i = 2; i < argc; i++){
        /*
         * NOTE: fnmatch returns zero if the string matches the pattern!
         */
        fprintf(stderr, "    '%s'", argv[i]);
        switch(fnmatch(pattern, argv[i], FNM_NOESCAPE|FNM_CASEFOLD)){
            case 0:
                fprintf(stderr, "YES\n");
                break;
            case FNM_NOMATCH:
                fprintf(stderr, "NO\n");
                break;
            default:
                fprintf(stderr, "ERROR in fnmatch\n");
                break;
        }
    }
    return 0;
}
