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
		if(c != '\n'){
			input = c;
			transition_a_faire = 1;
		}
		if(c == 'q') exit(0);
	}
	return NULL;
}

/*
 * REF https://stackoverflow.com/a/1798833
 * for
 * set_terminal_mode() and restore_terminal_mode()
 */
static struct termios oldt, newt;
void set_terminal_mode()
{

	/*
	 * Save current terminal attributs
	 */
    tcgetattr( STDIN_FILENO, &oldt);

	/*
	 * Create a copy of the old one and set some flags differently
	 */
    newt = oldt;
    /*
	 * turn off ICANON which normally takes care that one line at a time will 
	 * be processed that means it will return if it sees a "\n" or an EOF or an EOL
	 */
    newt.c_lflag &= ~( ICANON );

	/*
	 * Turn off echoing of typed characters
	 */
    newt.c_lflag &= ~( ECHO );

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
}

void restore_terminal_mode()
{
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

/*******************************************************************************
 * Appelé au début du main pour partir le thread
*******************************************************************************/
#define INPUT_CATCHING_STUFF_INIT \
	pthread_t input_thread;\
	pthread_create(&input_thread, NULL, check_input, NULL); \
	set_terminal_mode();

/*******************************************************************************
 * Appelé à la fin du main pour attendre sur le thread
*******************************************************************************/
#define INPUT_CATCHING_STUFF_END \
	pthread_join(input_thread, NULL);\
	restore_terminal_mode();
#endif
