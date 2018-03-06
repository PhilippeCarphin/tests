#include "state.h"
#include "transition.h"
/*******************************************************************************
 * Fonction qui retourne un nouvel état en fonction d'un état courant et d'une
 * entrée.
*******************************************************************************/
// Sous-routines
static State_t next_state_red(int input);
static State_t next_state_green(int input);
static State_t next_state_blue(int input);

State_t next_state(State_t state, int input)
{
	State_t new_state;
	switch(state){
		case RED:
			new_state =  next_state_red(input);
			break;
		case GREEN:
			new_state =  next_state_green(input);
			break;
		case BLUE:
			new_state =  next_state_blue(input);
			break;
	}
	return new_state;
}

static State_t next_state_red(int input)
{
	switch(input){
		case 'a': return BLUE;
		case 'b': return GREEN;
		default:  return RED;
	}
}
static State_t next_state_green(int input)
{
	switch(input){
		case 'c': return RED;
		case 'd': return BLUE;
		default:  return GREEN;
	}
}
static State_t next_state_blue(int input)
{
	switch(input){
		case 'e': return GREEN;
		case 'f': return RED;
		default:  return BLUE;
	}
}

