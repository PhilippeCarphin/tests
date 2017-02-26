#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQ_MAXFIELD 1000

int readline(char *line, int size,char* source)
{
  long int i = 0;
  register char c;
  while((c = source[i]) != '\n') {
    line[i++] = c;
    if(i > size)
    {
      printf("In the words of Tracy Jordan: Too small");
      return -1;
    }
  }
  line[i] = '\0';
  return i;
}

int main( int argc, char** argv)
{
  int i = 0;
  char defkey[SEQ_MAXFIELD],defval[SEQ_MAXFIELD];
  char* filename  = "./resources.def";
  printf("==============================\n");
  int fd = open(filename,O_RDWR|O_NONBLOCK);
  printf("here is the number of the file descriptor : %d \n", fd);
  printf("here is what happens when I open the same file : %d \n",
  open(filename, O_RDWR|O_NONBLOCK));
  return 0;
}
