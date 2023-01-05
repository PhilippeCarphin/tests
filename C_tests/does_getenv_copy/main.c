#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
 * This program demonstrates that the getenv() function does not return
 * a copy of the string for an environment variable's value but in fact
 * returns the address of that value in the environment memory layout.
 */

int demo_parse_seq_trace_level();

int main(void){

    printf("This process PID is %d\n", getpid());
    /*
     * Elementary demonstration that the pointer returned by getenv()
     * is a pointer pointing to the value in the environment.
     */
    char *home = getenv("HOME");
    strcpy(home, "Office 540");
    system("echo \"PID($$) HOME = $HOME\"");

    /*
     * When compiling without -DCOPY, the value at the the end will be
     * "A" because the ':' will have been replaced by '\0' and I am using
     * system(echo ...) to show that without a doubt we are modifying the
     * actual environment since child processes can see the change.
     */
    setenv("SEQ_TRACE_LEVEL", "A:B:C:D",1);
    system("echo \"PID($$) SEQ_TRACE_LEVEL (before) = '${SEQ_TRACE_LEVEL}'\"");
    demo_parse_seq_trace_level();
    system("echo \"PID($$) SEQ_TRACE_LEVEL (after)  = '${SEQ_TRACE_LEVEL}'\"");

    return 0;
}

struct SeqTraceOptions{
    int level;
    int show_datestamp;
    int yes_or_no;
};

static struct SeqTraceOptions seq_trace_options;

int demo_parse_seq_trace_level(){

#ifdef COPY
    /*
     * I prefer using automatic memory instead of using a quick strdup()
     * even if the function doesn't have multiple exit points.
     */
    char *trace_level = getenv("SEQ_TRACE_LEVEL");
    size_t size = strlen(trace_level) + 1;
    char tmp_trace_level[size];
    strncpy(tmp_trace_level, trace_level, size);
#else
    char *tmp_trace_level = getenv("SEQ_TRACE_LEVEL");
#endif

    for(char *tok = strtok(tmp_trace_level, ":");
              tok != NULL;
              tok = strtok(NULL, ":"))
    {
        if (strcmp(tok, "A") == 0){
            seq_trace_options.level = 8;
        } else if (strcmp(tok, "B") == 0){
            seq_trace_options.show_datestamp = 1;
        } else if (strcmp(tok, "C") == 0){
            seq_trace_options.yes_or_no = 1;
        } else {
            fprintf(stderr, "Unknown token '%s' in SEQ_TRACE_LEVEL\n", tok);
        }
    }
#ifdef COPY
    /*
     * No need to free because we used a variable length array
     */
#endif

    return 0;
}
