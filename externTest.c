#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQ_MAXFIELD 1000
/********************************************************************************
 * This test shows the use of the extern keyword in a context where it is
 * actually useless except maybe for readability.
********************************************************************************/
extern int globVar;
int globVar = 1;
int externTest()
{
	/*
	 * This following line could be omitted.  When referring to a global
	 * variable in the same file, this declaration is not necessary.
	 *
	 * I will make another test that will see if this can be used when the
	 * global variable is declared in another file.
	 */
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
