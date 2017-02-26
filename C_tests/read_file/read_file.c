#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
 * This file tests the reading of a file line by line.  It should be run like
 * so:
 *
 * ./a.out lipsum.txt
 *
 */

enum Constants {
	MAX_LINE_LENGTH = 1024,
};

int main(int argc, char **argv)
{
	printf("Reading a file line by line\n");
	if( argc < 2 ){
		printf("%s takes a filename as an argument\n",argv[0]);
		goto out;
	}

	/*
	 * Opening the file for reading
	 */
	FILE *file = NULL;
	if((file = fopen(argv[1], "r")) == NULL){
		perror("Error opening file :");
		goto out;
	}

	/*
	 * Reading the contents of the file line by line.  This is to make sure that
	 * I know how to do it.
	 */
	char line[1024];
	while(1){
		//fscanf(file, "%s\n", line);
		fgets(line, 1024, file);
		if(feof(file))
			break;
		printf("%s",line);
	}

out:
	return 0;
}
