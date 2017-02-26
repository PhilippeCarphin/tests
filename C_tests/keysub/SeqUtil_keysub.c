#include <stdlib.h>
#include <string.h>

#define SEQ_MAXFIELD 2048
/* Some context about strtok_r(string,delim,&saveptr).
 *
 * Suppose you have a string that you want to break up into tokens delimited by
 * something.  Say the words of a sentence.
 *
 * str = "This is a sentence, it has some words in it."
 *
 * strtok will return the first 'token'.  It does this by changing the first
 * delimiter for a NUL byte (a char that marks the end of a C-string.  But if
 * you do that, you lose the rest of the string.  That's what saveptr is for.
 * You pass the adress of saveptr to strtok, and it will put the start of the
 * rest of the string (after skipping any other delimiters) in saveptr.
 *
 * For illustration purposes, I will use '#' to represent the NUL byte that
 * indicates the end of a C-string
 * 
 * So if I do 
 *
 * t = strtok(str," ,.",&saveptr);
 *
 * I get 
 *
 *    saveptr
 *      v
 * This#is a sentence, it has some words in it.#
 * ^   ^
 * t  NUL BYTE HERE
 *
 * so t = "This"
 *
 * then, when I call strtok the subsequent times, I give it NULL as it's first
 * argument, and that tells it to use saveptr as the input string
 *
 * t = strtok(NULL," ,.",&saveptr);
 *
 *       saveptr
 *         v
 * This#is#a sentence, it has some words in it.#
 *      ^ ^
 *      t NUL BYTE HERE
 *
 * t = "is"
 *
 * And again:
 *
 * t = strtok(NULL," ,.",&saveptr);
 *
 *         saveptr
 *           v
 * This#is#a#sentence, it has some words in it.#
 *         ^^
 *         t|
 *          NUL BYTE HERE
 *
 * t = "a"
 *
 * And so on until there are no more tokens.  At which point strtok will return
 * NULL so the classical idiom for iterating over the tokens of a string is
 *
 * t = strtok_r(str," ,.",&saveptr);
 * while(t != NULL)
 * {
 *    do stuff with token
 *
 *    t = strtok_r(NULL," ,.",&saveptr);
 * }
 *
 * One thing about strtok, it ruins your input string because it puts NUL bytes
 * everywhere.  So unless you want to sacrifice it, you have to make a copy of
 * it. 
 *
 * In the case of the following function, strtok_r() is just not the right tool
 * for the job.  In fact, I suspect that the guy thought he should use strtok()
 * and when he started having to do weird stuff, instead of stepping back and
 * figuring out what he wanted to do, he just added weird if( something )'s
 * everywhere until it worked.
 *
 */

/* Substitutes a ${.} formatted keyword in a string. To use a definition file (format defined by
   SeqUtils_getdef(), provide the _deffile name; a NULL value passed to _deffile 
   causes the resolver to search in the environment for the key definition.  If 
   _srcfile is NULL, information about the str source is not printed in case of an error.*/
char* SeqUtil_keysub( const char* _str, const char* _deffile, const char* _srcfile ,const char* _seq_exp_home) {
  char *strtmp=NULL,*substr=NULL,*var=NULL,*env=NULL,*post=NULL;
  const char *source;
  char *saveptr1,*saveptr2;
  static char newstr[SEQ_MAXFIELD];
  int start,isvar;

  if (_deffile == NULL){
    source = "environment";
  } else {
    source = "definition";
  }

  strtmp = (char *) malloc( strlen(_str) + 1 ) ;
  strcpy(strtmp,_str);
  /*
   * strtmp = "This_${word1}_a_${word2}."
   */
  substr = strtok_r(strtmp,"${",&saveptr1); /* Strtok splits a string into two
                                               strings, one is the original
                                               string but cut off at the first
                                               occurrence of a delimiter and the
                                               other is the string after the
                                               delimiters. */
  /*
   * This_
   * ^
   * subsrt
   *
   * word1}_a_${word2}.
   * ^
   * saveptr1
   */
  start=0;
  while (substr != NULL){
    isvar = (strstr(substr,"}") == NULL) ? 0 : 1;
    /*
     * Isvar = 1 if there is a "}" and 0 otherwise.
     * Here isvar == 0.
     */
    var = strtok_r(substr,"}",&saveptr2);
    /*
     * This_
     * ^
     * var
     *
     * saveptr2 is NULL
     */

    /*
     * If isvar == 0, then we shouldn't even look for a value for that variable.
     */
    if (strcmp(source,"environment") == 0){
      env = getenv(var);
    }else{
      env = SeqUtil_getdef(_deffile,var,_seq_exp_home);
    }
    post = strtok_r(NULL,"\0",&saveptr2); /* Calling strtok() with "\0" as a delimiter is just rediculous. */
    /*
     * post == NULL here
     */
    if (env == NULL){
       /*
        * We didn't find a value for the variable, but maybe it wasn't even a
        * variable
        */
      if (isvar > 0){
         /*
          * If it was a variable, then that was an error; make the program crash
          */
	      raiseError("Variable %s referenced by %s but is not set in %s\n",var,_srcfile,source);
       }else{
         /*
          * But it wasn't a variable this time, so copy var (which is actually
          * not a variable) into our output.
          */
	      strncpy(newstr+start,var,strlen(var));
         /*
          * This_
          * ^
          * newStr
          */
	      start += strlen(var);
      }
    } else {
       /* Not doing this the first time around */
      strncpy(newstr+start,env,strlen(env));
      start += strlen(env);
    }

    if (post != NULL){
       /* post is NULL so we're not doing this */
      strncpy(newstr+start,post,strlen(post));
      start += strlen(post);
    }
    /*
     * Put a NUL byte at the end of newstr.  THis is only useful at the end, so
     * it could be done outside the while.
     */
    newstr[start]=0;

    /*
     * Advance to the next iteration.  Before the strtok call:
     *
     * word1}_a_${word2}.
     * ^
     * saveptr1
     */
    substr = strtok_r(NULL,"${",&saveptr1); /* If the first argument is NULL,
                                               then it will use the string given
                                               by saveptr1 as it's input */
    /*
     * word1}_a_
     * ^
     * substr
     *
     * word2}.
     * ^
     * saveptr1
     */

    /* I'm putting the next iteration here because it will have different
     * comments than the first one.*/

    isvar = (strstr(substr,"}") == NULL) ? 0 : 1;
    /*
     * isvar == 1 here because substr does contain "}"
     */
    var = strtok_r(substr,"}",&saveptr2);
    /*
     * word1
     * ^
     * var
     *
     * _a_
     * ^
     * saveptr2
     */
    if (strcmp(source,"environment") == 0){
      env = getenv(var);
    }else{
      env = SeqUtil_getdef(_deffile,var,_seq_exp_home);
    }
    /*
     * This time, hopefully, env is the value of the variable with name "word1".
     */
    post = strtok_r(NULL,"\0",&saveptr2); /* Calling strtok() with "\0" as a delimiter is just rediculous. */
    /*
     * _a_
     * ^
     * post
     */
    if (env == NULL){
       /* Not doing this because we found a value for word1 */
      if (isvar > 0){
	      raiseError("Variable %s referenced by %s but is not set in %s\n",var,_srcfile,source);}
      else{
	      strncpy(newstr+start,var,strlen(var));
	      start += strlen(var);
      }
    }
    else {
       /* Copy */
      strncpy(newstr+start,env,strlen(env));
      start += strlen(env);
      /* 
       * This_is
       * ^      ^
       * newstr |
       *        newstr+start
       */
    }

    if (post != NULL){
       /* post is NULL so we're not doing this */
      strncpy(newstr+start,post,strlen(post));
      start += strlen(post);
      /*
       * This_is_a_
       * ^         ^
       * newstr    |
       *           newstr+start
       */
    }
    /*
     * Put a NUL byte at the end of newstr.  THis is only useful at the end, so
     * it could be done outside the while.
     */
    newstr[start]=0;

    /* It took two iterations to replace one variable with it's value.
     * Here we have
     *
     * word2}.
     * ^
     * saveptr1
     */

    /*
     * Now we move on to the next iteration
     */

    substr = strtok_r(NULL"${",&saveptr1);

    /*
     * word2}.
     * ^
     * substr
     *
     * saveptr1 == NULL so this is the last iteration.
     */

    isvar = (strstr(substr,"}") == NULL) ? 0 : 1;
    /*
     * Here isvar == 1.
     */
    var = strtok_r(substr,"}",&saveptr2);
    /*
     * word2
     * ^
     * var
     *
     * .
     * ^
     * saveptr2
     */
    if (strcmp(source,"environment") == 0){
      env = getenv(var);
    }else{
      env = SeqUtil_getdef(_deffile,var,_seq_exp_home);
    }
    post = strtok_r(NULL,"\0",&saveptr2); /* Calling strtok() with "\0" as a delimiter is just rediculous. */
    /*
     * post = "."
     */
    if (env == NULL){
      if (isvar > 0){
	      raiseError("Variable %s referenced by %s but is not set in %s\n",var,_srcfile,source);
       }else{
	      strncpy(newstr+start,var,strlen(var));
	      start += strlen(var);
      }
    } else {
      strncpy(newstr+start,env,strlen(env));
      start += strlen(env);
      /*
       * This_is_a_string
       * ^               ^
       * newstr        newstr+start
       */
    }

    if (post != NULL){
      strncpy(newstr+start,post,strlen(post));
      start += strlen(post);
      /*
       * This_is_a_string.
       * ^                ^
       * newstr          newstr+start
       */
    }
    /*
     * Put a NUL byte at the end of newstr.  THis is only useful at the end, so
     * it could be done outside the while.
     */
    newstr[start]=0;
  }

/*
 * We're finally done, it took me as much time to figure out how an already
 * written function works than it took me to actually code a sensible function
 * that does the same thing.
 */
  free(strtmp);
  return newstr;
}  
