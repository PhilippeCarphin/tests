#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdio.h>

/*
 * Convenience function to get short duration delays
 */
void sleep_ms(int ms);

/*
 * Obtain the with of the terminal using ioctl.
 */
int get_term_width()
{
  struct winsize w;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

/*
 * Prints the loading bar with and demonstrates the use of control
 * characters to control where things go on the terminal
 */
int progress_callback(int percent)
{
  int length = ( get_term_width() * percent ) / 100;

  /*
   * Printing a \r character puts the cursor back at the start of the line
   */
  fputc('\r', stderr);

  /*
   * Print a bar of '#' of the required length, nothing fancy here
   */
  for(int i = 0; i < length; ++i){
    fputc('#', stderr);
  }

  /*
   * Printing another '\r' to place the cursor back at the start of the line
   * This is so that print statements made by other functions will overwrite
   * the progress bar
   */
  fputc('\r', stderr);
  return 0;
}

int main(int argc, char **argv){
  (void) argc;
  (void) argv;

  /*
   * A for loop that represents a long running calculation
   */
  for(int i = 0; i < 100; i++){

    /*
     * Periodically, we print the progress bar
     */
    progress_callback(i);

    /*
     * Every 8 iterations, print a message.
     * This demonstrates the use of \33[2K which clears the line
     * that the cursor is on
     */
    if(i % 8 == 0){
      fprintf(stderr, "\33[2KThis is a print statement with the 'clear-line' char\n");
    }

    /*
     * Every 13, print but without clearing.  We can see that
     * although the progress bar returns the cursor to the front
     * of the line, it doesn't erase the '#' that are on it
     * so when we print, only the ones we print over are erased
     * and the rest stay there.
     */
    if(i % 13 == 0){
      fprintf(stderr, "This is a message without the clear\n");
    }
    sleep_ms(100);
  }
  return 0;
}

void sleep_ms(int ms){
  struct timespec ts = {0, 1000000 * ms};
  nanosleep(&ts, NULL);
}
