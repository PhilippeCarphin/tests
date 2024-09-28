#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

/*
 * This test is used to isolate the behavior of the C regex library.
 *
 * When this library is used within real programs it can be tedious to troubleshoot
 * because this library's role is but a small part of that program's execution.
 */

int main(int argc, char **argv)
{
    if(argc < 3){
        fprintf(stderr, "USAGE: %s PATTERN STRING [STRINGS ...]\n", argv[0]);
        return 1;
    }

    regex_t regex;
    int err = regcomp(&regex, argv[1], REG_EXTENDED);
    if (err) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    fprintf(stderr, "Regex '%s' compiled, .re_nsub=%lu\n", argv[1], regex.re_nsub);

    /*
     * We use .re_nsub+1 here because the number of matches is the full match
     * plus the number of subexpressions.
     */
    regmatch_t rm[regex.re_nsub+1];

    for(int i = 2; i < argc; i++){
        fprintf(stderr, "Applying regex to '%s'\n", argv[i]);

        int err = regexec(&regex, argv[i], regex.re_nsub+1, rm, 0);
        if(err == REG_NOMATCH){
            fprintf(stderr, "==> NO_MATCH\n");
            continue;
        }

        for(size_t j = 0; j <= regex.re_nsub; j++){
            regmatch_t match = rm[j];
            size_t len = (match.rm_eo - match.rm_so);
            char *buf = malloc(len+1);
            strncpy(buf, argv[i]+match.rm_so, len);
            buf[len] = '\0';
            fprintf(stderr, "    match_object[%lu]: '%s' (.re_so=%d, .re_eo=%d)\n", j, buf, match.rm_so, match.rm_eo);
        }
    }
}
