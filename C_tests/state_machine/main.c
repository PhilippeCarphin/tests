#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "transition.h"
#include "state.h"
#include "action.h"
#include "termios.h"
const int debug = 0;

// Variable globale représentant l'état courant de notre machine à état
volatile State_t current_state = RED;

// Consommation d'input sur STDIN et signalement main thread qu'une transition
// doit être faite
volatile int input;
volatile int finished = 0;
volatile int transition_a_faire = 0;

/*******************************************************************************
 * Ce programme exécute continuellement l'action correspondant à l'état courant
 * et vérifie si une entrée doit être consommée pour faire une transition
 * d'état.
*******************************************************************************/
#include "hidden_code.h" // Some code is hidden to make the interesting part clearer
int main(void)
{
    // INPUT_CATCHING_STUFF_INIT;
	pthread_t input_thread;
	pthread_create(&input_thread, NULL, check_input, NULL);
	set_terminal_mode();

	for(;;){
		if(transition_a_faire){
			current_state = next_state(current_state, input);
			transition_a_faire = 0;
		}
		state_action(current_state);
        if(finished){
            break;
        }
	}

    // INPUT_CATCHING_STUFF_END;
	pthread_join(input_thread, NULL);
	restore_terminal_mode();
	return 0;
}

