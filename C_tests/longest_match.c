#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

char input[] =
"./src/ca/polymtl/inf8480/tp1/server/Server.java\n\
./src/ca/polymtl/inf8480/tp1/client/FakeServer.java\n\
./src/ca/polymtl/inf8480/tp1/client/Client.java\n\
./src/ca/polymtl/inf8480/tp1/shared/SyncedFile.java\n\
./src/ca/polymtl/inf8480/tp1/shared/Lock.java\n\
./src/ca/polymtl/inf8480/tp1/shared/Response.java\n\
./src/ca/polymtl/inf8480/tp1/shared/ServerInterface.java\n";

size_t line_match_length(const char *line1, const char *line2)
{
	const char *p;
	const char *q;
	for(p = line1, q = line2;
			*p != '\0' && *q != '\0' && *p != '\n' && *q != '\n';
			++p, ++q)
	{
		if(*p != *q){
			break;
		}
	}
	return p - line1;
}
int line_count(const char *string){
	int lc = 0;
	for(const char *p = string; *p != '\0'; ++p){
		if(*p == '\n'){
			lc++;
		}
	}
	return lc;
}

int tokenize_on_lines(char *string, char **lines){
	*lines++ = string;
	for(char *s = strtok(string, "\n"); (s = strtok(NULL, "\n")) != NULL; ){
		*lines++ = s;
	}
	*lines = NULL;
	return 0;
}

int main(void)
{
	int lc = line_count(input);
	char *lines[line_count(input) + 1];
	tokenize_on_lines(input, lines);

	int min_match_length = strlen(lines[0]);
#if 1
	char **line = lines;
	while(*++line != NULL){
		int match_length = line_match_length(lines[0], *line);
		if(match_length < min_match_length){
			min_match_length = match_length;
		}
	}
#else
	for(int i = 1; i < lc; ++i){
		int match_length = line_match_length(lines[0], lines[i]);
		if(match_length < min_match_length){
			min_match_length = match_length;
		}
	}
#endif

	for(int i = 0; i < min_match_length; ++i){
		putchar(lines[0][i]);
	}
	putchar('\n');
}
