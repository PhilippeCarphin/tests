#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/********************************************************************************
 * Name        : Basic string manipulation functions for the parser
 * Description : Used to handle whitespace, comments checking prefixes
 *******************************************************************************/
int starts_with(const char *line, const char *prefix);
#define IS_WHITE(x) ((x) == ' ' || (x) == '\t' || (x) == '\n');
int is_white(const char *line);
int ignore_line(const char *line);

/*
 * Parser state and response
 */
struct Parser {
   FILE *f;
   int   line;
   const char *key;
   char *obs_query;
   char *elem_query;
};

/********************************************************************************
 * Name        : cpfgets(char *s, int n, struct Parser *this)
 * Description : Wrapper for doing fgets and incrementing the current line in
 *               the parser state for error reporting.
 * Arguments   : s : out param for the string read from the filename
 *               n : max number of chars to read
 *            this : Parser state
 * Return      : Pointer to string read from file
 * Remarks     : 
 *******************************************************************************/
static char *cpfgets(char *s, int n, struct Parser *this)
{
   this->line++;
   return fgets(s, n, this->f);
}

static int ParseFile(struct Parser *this);
int get_values(const char *Filename, const char *Key, char **ObsObjectOut, char **ElemObjectOut)
{
   FILE *f;
   if((f = fopen(Filename, "r")) == NULL){
      fprintf(stderr, "ERROR: Could not open config file  %s\n", Filename);
      return -1;
   }

   struct Parser skv = {f,0, Key, NULL, NULL};

   if(ParseFile(&skv)){
      return -1;
   }

   *ObsObjectOut = strdup(skv.obs_query);
   *ElemObjectOut = strdup(skv.elem_query);

   return 0;
}

/********************************************************************************
 * Name        : ParseFile(struct Parser *this)

 * Description : Drives the parsing of container across the loaded file. Ignores
 *               all lines until a line is found starting with '#BEGIN_CONTAINER
 *               xyz'. It extracts the key and if it matches, the function hands
 *               control to ParseContainer. If the key doens't match, then it
 *               continues till the next '#BEGIN_CONTAINER abc'.
 * Arguments   : this (the parser state)
 * Return      : Standard error codes
 * Remarks     : The only thing we are allowed to see in this state is
 * #BEGIN_CONTAINER, anything else is an error.
 *******************************************************************************/
static int ParseContainer(struct Parser *this);
static int SkipContainer(struct Parser *this);
static int ParseFile(struct Parser *this)
{
   char line[1024];
   char buff[1024];

   while(cpfgets(line, sizeof(line), this)){
      if(ignore_line(line))
         continue;

      if(!starts_with(line, "#BEGIN_CONTAINER ")){
         fprintf(stderr, "PARSE_FILE : UNEXPECTED TOKEN AT LINE %d\n", this->line);
         return -1;
      }

      if(sscanf(line, "#BEGIN_CONTAINER %20s", buff) != 1){
         fprintf(stderr, "COULD NOT EXTRACT CONTAINER NAME FROM LINE %d\n", this->line);
         return -1;
      }

      if(strcmp(buff, this->key) != 0){
         if(SkipContainer(this))
            return -1;
      } else {
         return ParseContainer(this);
      }
   }

   fprintf(stderr, "KEY '%s' NOT FOUND IN FILE\n", this->key);
   return -1;
}

/********************************************************************************
 * Name        : SkipContainer(struct Parser *this)
 * Description : Advance the parser past the next #END_CONTAINER token
 * Arguments   : this (the parser state)
 * Return      : Standard error codes
 * Remarks : Ignores everything except #END_CONTAINER which signals that we're
 *           done, and #BEGIN_CONTAINER which is an error.
 *******************************************************************************/
static int SkipContainer(struct Parser *this)
{
   char line[1024];
   while(cpfgets(line, sizeof(line), this)){
      if(starts_with(line, "#END_CONTAINER")){
         return 0;
      } else if(starts_with(line, "#BEGIN_CONTAINER")){
         fprintf(stderr, "UNEXPECTED '#BEGIN_CONTAINER' on line %d\n", this->line);
         return -1;
      }
   }
   fprintf(stderr, "UNEXPECTED END OF FILE WHILE LOOKING FOR '#END_CONTAINER'\n");
   return -1;
}

/********************************************************************************
 * Name        : ParseContainer(struct Parser *this)
 * Description : Parse the inside of a #BEGIN_CONTAINER ... #END_CONTAINER
 * Arguments   : this (the parser state)
 * Return      : standard error codes
 * Remarks     : The only token allowed is #BEGIN_OBJECT, which causes a change
 *               to the ParseObject state and #END_CONTAINER which causes an exit
 *               from this state.
 *******************************************************************************/
static int ParseObject(struct Parser *this, const char *query_name);
static int ParseContainer(struct Parser *this)
{
   char line[1024];
   char query_name[1024];

   while(cpfgets(line, sizeof(line), this)){
      if(ignore_line(line))
         continue;

      if(starts_with(line, "#END_CONTAINER")){
         return 0;
      }

      if(!starts_with(line, "#BEGIN_OBJECT")){
         fprintf(stderr, "UNEXPECTED TOKEN WHILE PARSING CONTAINER AT LINE %d\n", this->line);
         return -1;
      }

      if(sscanf(line, "#BEGIN_OBJECT %20s", query_name) != 1){
         fprintf(stderr, "Could not get query name from line %d\n", this->line);
         return -1;
      }

      if(ParseObject(this, query_name)){
         return -1;
      }
   }
   fprintf(stderr, "UNEXPECTED END-OF-FILE WHILE PARSING CONTAINER");
   return -1;
}

/********************************************************************************
 * Name        : ParseObject(struct Parser *this, const char *query_name)
 * Description : Parse a query (basically accumulates all the text up to
 *               #END_OBJECT)
 * Arguments   : this (parser state)
 *               query_name (name parsed by ParseContainer when it saw the
 *                          #BEGIN_OBJECT line)
 *                          It is used to decide where to put the query text in
 *                          the parser's response fields
 * Return      : standard error codes
 * Remarks     : #END
 *******************************************************************************/
static int ParseObject(struct Parser *this, const char *query_name)
{
   char line[1024];
   char query_str[4096] = {0};
   int query_start = this->line;
   while(cpfgets(line, sizeof(line), this)){
      if(ignore_line(line))
         continue;

      if(starts_with(line, "#END_OBJECT")){
         goto done;
      }

      if(starts_with(line, "#BEGIN") || starts_with(line, "#END")){
         fprintf(stderr, "Parsing Object : UNEXPECTED TOKEN at line %d\n", this->line);
         return -1;
      }

      size_t space_left = sizeof(query_str) - strlen(query_str) - 1;
      if(space_left < strlen(line)){
         fprintf(stderr, "Your query is too long for %s()'s buffer of 4096 chars\n", __func__);
      }
      strncat(query_str, line, space_left);;
   }

   fprintf(stderr, "UNEXPECTED END OF FILE");
   return -1;

done:
   if(strcmp("obs", query_name) == 0)
      this->obs_query = strdup(query_str);
   else if (strcmp("elem", query_name) == 0)
      this->elem_query = strdup(query_str);
   else {
      fprintf(stderr,"UNRECOGNIZED OBJECT NAME '%s' at line %d\n", query_name, query_start);
      return -1;
   }
   return 0;
}


/********************************************************************************
 * Check if prefix is a prefix of line
 ********************************************************************************/
int starts_with(const char *line, const char *prefix){
   return strncmp(line, prefix, strlen(prefix)) == 0;
}

/********************************************************************************
 * check if a line is only whitespace
 ********************************************************************************/
int is_white(const char *line)
{
   const char *s = line;
   char c;
   while((c = *(s++)) != 0){
      if(!((c) == ' ' || (c) == '\t' || (c) == '\n')){
         return 0;
      }
   }
   return 1;
}

/********************************************************************************
 * Check if a line is to be ignored
 ********************************************************************************/
int ignore_line(const char *line)
{
   return starts_with(line, "//") || is_white(line);
}

#ifdef _SELF_TEST
/*
 * This file can be compiled and run without any external dependencies.  If it
 * is compiled with -D_SELF_TEST, then it can be run as an executable for
 * testing in isolation.  Something like:
 *
 *     gcc -o parser simple-parser.c -D_SELF_TEST ; ./parser infile.txt
 *
 */
int main(int argc, char *argv[])
{
   char *first_val;
   char *second_val;

   const char *infile = (argc > 1 ? argv[1] : "infile.txt");

   char *key = "key1";
   /*
    * This test should be successful
    */
   if(get_values(infile, key, &first_val, &second_val)){
      fprintf(stderr, "MAIN: Could not get values for key %s\n", key);
      return -1;
   }
   fprintf(stderr, "========== Values for %s ==============\n", key);
   fprintf(stderr, "========== obs query ================\n%s", first_val);
   fprintf(stderr, "========== elem query ===============\n%s", second_val);
   fprintf(stderr, "========================================\n\n");

   /*
    * This test should fail because the key is not in the file
    */
   key = "key2";
   if(get_values(infile , "key2", &first_val, &second_val)){
      fprintf(stderr,
            "MAIN: Could not get values for key (As expected because "
            "there is no container named 'key2' %s\n",
            "key2");;
   }

   key = "notkey2";
   if(get_values(infile , key, &first_val, &second_val)){
      fprintf(stderr, "MAIN: Could not get values for key %s\n", key);
      return -1;
   }
   fprintf(stderr, "\n========== Values for %s ==============\n", key);
   fprintf(stderr, "========== obs query ================\n%s", first_val);
   fprintf(stderr, "========== elem query ===============\n%s", second_val);
   fprintf(stderr, "========================================\n\n");

   return 0;
}
#endif
