#ifndef _HIDDEN_CODE_H_
#define _HIDDEN_CODE_H_
#include <pthread.h>
/*
 * Bouts de code que qui ne sont pas propres à la conception d'une machine à
 * état.
 */

/*******************************************************************************
 * Worker de thread qui consomme les caractères du terminal.
*******************************************************************************/
void *check_input(){
	char c;
	while(1){
		c = getchar();
		fflush(stdin);
		if(c != '\n'){
			input = c;
			transition_a_faire = 1;
		}
		if(c == 'q') exit(0);
	}
	return NULL;
}

/*******************************************************************************
 * Appelé au début du main pour partir le thread
*******************************************************************************/
#define HIDDEN_START \
	pthread_t input_thread;\
	pthread_create(&input_thread, NULL, check_input, NULL);

/*******************************************************************************
 * Appelé à la fin du main pour attendre sur le thread
*******************************************************************************/
#define HIDDEN_END \
	pthread_join(input_thread, NULL);
#endif
