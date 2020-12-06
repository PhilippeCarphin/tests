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

/*
 * Function to print messages in the context of a progress bar.
 * It simply prints the users message but clears the line first
 * and adds a newline */
int progress_message(char *message){
  /*
   * This prints a control char that clears the line.
   * clearline EL2         Clear entire line                      ^[[2K
   * From http://www.climagic.org/mirrors/VT100_Escape_Codes.html
   */
  fprintf(stderr, "[2K%s\n", message);
  return 0;
}

int main(int argc, char **argv){
  (void) argc;
  (void) argv;

  /*
   * A for loop that represents a long running calculation
   * does its thing but also calls the progress callback
   * at every iteration.  Inside the loop, it uses progress_message()
   * to print messages that clear the line.
   *
   * This loop calls the callback, demonstrates why the
   * progress_message function is useful by printing without
   * it.
   *
   * Also you want to print your messages right before the
   * bar is about to be redrawn. This way it will look like
   * the messages are appearing above the bar.
   */
  for(int i = 0; i < 100; i++, progress_callback(i)){


    /*
     * Iterations of this loop are long hence the progress bar
     */
    sleep_ms(100);

    /*
     * Every 8 iterations, print a message.
     * This demonstrates the use of \33[2K which clears the line
     * that the cursor is on
     */
    if(i % 9 == 0){
        progress_message("This is a print statement with the 'clear-line' char");
    }

    /*
     * Every 21, print but without clearing.  We can see that
     * although the progress bar returns the cursor to the front
     * of the line, it doesn't erase the '#' that are on it
     * so when we print, only the ones we print over are erased
     * and the rest stay there.
     */
    if(i % 23 == 0){
      fprintf(stderr, "This is a message without the clear\n");
    }
  }
  return 0;
}

void sleep_ms(int ms){
  struct timespec ts = {0, 1000000 * ms};
  nanosleep(&ts, NULL);
}
