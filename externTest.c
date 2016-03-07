#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQ_MAXFIELD 1000
extern int globVar;
int globVar = 1;
int externTest()
{
  extern int globVar;
  return globVar++;
}


int main( int argc, char** argv)
{
  int i = 0;
  while(i++ < 10)
  {
    printf("Global test: %d\n",externTest());
  }
}
