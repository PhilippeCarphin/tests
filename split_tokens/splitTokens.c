#include <string.h>

#define MAX_TOKENS 30
#define MAX_LENGTH 2048
int droppedTokens = 0;

/********************************************************************************
 * Returns a NULL terminated table of char *.  One for each token of the string
 * src separated by the delimiters delim.
 *
 * Iterating over the tokens can be done as follows:
 *
 * const char **tokens = getTokens(str, delim);
 * int i = 0;
 * char *token = NULL;
 * while( (token = tokens[i++]) != NULL )
 * {
 *    printf("%s\n", token);
 * }
 *
 * If the string is too long, the function will return NULL; if there are more
 * than MAX_TOKENS tokens, they will be dropped;
********************************************************************************/
const char **getTokens(const char *src, const char *delim)
{
   static char str[MAX_LENGTH];
   static char *tokens[MAX_TOKENS];

   if( strlen(src) >= MAX_LENGTH)
      return NULL;

   strncpy(str, src, MAX_LENGTH);
   
   /* Just to avoid errors if the input string is too long. */
   str[MAX_LENGTH-1] = '\0';


   char *tok = NULL;
   int i = 0;
   for(tok = strtok(str,delim); i < MAX_TOKENS && tok != NULL; tok = strtok(NULL, delim))
      tokens[i++] = tok;
   tokens[i] = NULL;

   return (const char **)tokens;
}


