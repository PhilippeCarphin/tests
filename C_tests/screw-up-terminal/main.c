#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios ttyOrig;

void ttyReset(void)
{
    if(tcsetattr(STDIN_FILENO, TCSANOW, &ttyOrig) == -1){
        exit(77);
    }
}

int ttySetRaw(int fd, struct termios *prefTermios)
{
    struct termios t;

    if(tcgetattr(fd, &t) == -1){
        return -1;
    }

    if(prefTermios != NULL){
        *prefTermios = t;
    }

    t.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
    t.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR | INPCK | ISTRIP | IXON | PARMRK);

    t.c_oflag &= ~OPOST;

    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;

    if(tcsetattr(fd, TCSAFLUSH, &t) == -1){
        return -1;
    }

    return 0;
}


int main(int argc, char **argv){
  int reset_on_exit = 0;
  if(argc > 1){
    reset_on_exit = 1;
  }

  if(ttySetRaw(STDIN_FILENO, &ttyOrig)){
    exit(1);
  }

  if(reset_on_exit){
    // Normally would use atexit(ttyReset)
    // which is why ttyOrig is a global variable
    ttyReset();
  }

  return 0;
}
