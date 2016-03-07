#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQ_MAXFIELD 1000
int initPhil = 0;
int uninitPhil;
int readline(char *line, int size,char* source)
{
  uninitPhil = 18;
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
  initPhil = 16;
  return i;
}

int main( int argc, char** argv)
{
  int i = 0;
  char defkey[SEQ_MAXFIELD],defval[SEQ_MAXFIELD];
  char* filename  = "./resources.def";
  printf("==============================\n");
  /* int fd = open(filename,O_RDWR|O_NONBLOCK);
  printf("here is the number of the file descriptor : %d \n", fd);
  printf("here is what happens when I open the same file : %d \n",
	*/
int fd = open(filename,O_RDWR|O_NONBLOCK);
lseek(fd,0,SEEK_END);
char e;
int stat = read(fd,&e,1);
printf("Char e is : %x\n", e);

if(e != '\n')
	write(fd,"\n",1);
close(fd);



  fd = open(filename, O_RDWR|O_NONBLOCK);
  struct stat fileStat;
  fstat(fd,&fileStat);
  char* addr = mmap(NULL, fileStat.st_size, PROT_READ, MAP_SHARED, fd, 0); 
  close(fd);
  char *current = addr,
       *fileend = addr + fileStat.st_size;
  char* line = (char*)malloc(1000);
	char c;
	do{
		c = *current;
		current++;
		// printf("%x -- %c \n", c,c);
	}while(current <= fileend + 10);

	printf("the value of backslash 0: %x \n", '\0');




	
  return 0;
}
