#include <unistd.h>
#include <stdio.h>
#include <tcl.h>
#include <expect_comm.h>
#include <expect_tcl.h>
#include <expect.h>

int main(int argc, char **argv)
{
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);
    Expect_Init(interp);

    FILE *f = exp_popen("/opt/homebrew/bin/bash");
    if(f == NULL){
        return 1;
    }
    // int bash = exp_spawnl("/opt/homebrew/bin/bash", "/opt/homebrew/bin/bash", NULL);
    // fprintf(stderr, "bash=%d\n", bash);
    // execl("/opt/homebrew/bin/bash", "/opt/homebrew/bin/bash", NULL);

    return 0;
}

