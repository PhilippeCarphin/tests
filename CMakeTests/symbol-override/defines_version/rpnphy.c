#include <stdio.h>


void rpnphy_do_physics_original();
void rpnphy_do_physics_custom();
void rpnphy_do_physics(void)
{
#ifdef USE_OVERRIDES
    rpnphy_do_physics_custom();
#else
    rpnphy_do_physics_original();
#endif
}

void rpnphy_do_physics_original()
{
    printf("This is the %s() \033[1;32m(ORIGINAL)\033[0m implemented in %s\n", __func__, __FILE__);
}

void rpnphy_do_ligth_polarization(void)
{
    printf("This is the %s() implemented in %s\n", __func__, __FILE__);
}

void rpnphy_do_more_physics(void)
{
    printf("This is the %s() implemented in %s\n", __func__, __FILE__);
}

void rpnphy_do_physics_custom(void)
{
    printf("This is the %s() \033[1;36m(CUSTOM)\033[0m implemented in %s\n", __func__, __FILE__);
}
