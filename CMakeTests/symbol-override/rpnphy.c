#include <stdio.h>

void rpnphy_do_physics(void)
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
