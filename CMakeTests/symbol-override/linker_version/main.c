#include "gemdyn.h"
#ifdef WITH_SHADES
    #include "rpnshades.h"
#endif

int main(void){

    gemdyn_do_a_timestep();

#ifdef WITH_SHADES
    printf("PISS BUCKET\n");
    rpnshades();
#endif

    return 0;

}
