#include "action.h"
#include <unistd.h> // for sleep()
#include <stdio.h>
/*******************************************************************************
 * Fonction qui représente une action qui serait prise selon l'état.
*******************************************************************************/
static void red_action();
static void green_action();
static void blue_action();

void state_action(State_t state)
{
	switch(state){
		case RED:
			red_action();
			break;
		case GREEN:
			green_action();
			break;
		case BLUE:
			blue_action();
			break;
	}
	sleep(1);
}

void red_action()
{
	printf("%s()\n", __FUNCTION__);
}

void green_action()
{
	printf("%s()\n", __FUNCTION__);
}

void blue_action()
{
	printf("%s()\n", __FUNCTION__);
}
