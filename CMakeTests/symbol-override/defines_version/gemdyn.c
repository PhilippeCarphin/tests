#include <stdio.h>
#include "rpnphy.h"
#ifdef USE_OVERRIDES
    #include "rpnphy-custom.h"
#endif

void gemdyn_do_a_timestep()
{
    printf("This is %s() initializint timestep\n", __func__);

    printf("This is %s() calling rpnphy_do_physics()\n", __func__);

#if METHOD == DEFINES
 #ifdef USE_OVERRIDES
     rpnphy_do_physics_custom();
 #else
     rpnphy_do_physics();
 #endif
#else
     rpnphy_do_physics();
#endif

    rpnphy_do_more_physics();

    printf("This is %s() : END\n", __func__);
}
