#include <stdio.h>
#define __USE_GNU
#include <errno.h>

int main(int argc, char**argv)
{

    fprintf(stderr, "argv[0]='%s'\n", argv[0]);
    fprintf(stderr, "program_invocation_name='%s'\n", program_invocation_name);
    fprintf(stderr, "program_invocation_shortname='%s'\n", program_invocation_short_name);
    return 0;
}
