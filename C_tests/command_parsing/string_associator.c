#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "string_associator.h"

/******************************************************************************
 * Changes string in place to lower case
 ******************************************************************************/
char *tolower_str(char *str)
{
	char *s = str;
	while(*s){
		*s = tolower((unsigned int) *s);
		s++;
	}
	return str;
}

/******************************************************************************
 * Returns the integer (usually from enum) associated to the string as defined
 * by the string_associator array.
 ******************************************************************************/
int int_associated_to(char *str, struct string_associator *ass)
{
	printf("%s() str = %s \n",__FUNCTION__, str);
	int retval;
	
	char *s = tolower_str(strdup(str));
	for(struct string_associator *p = ass; p->str_val != NULL; ++p){
		printf("\texamining : p->str_val:%s -- p->int_val:%d\n", p->str_val, p->int_val);
		if(strcmp(s, p->str_val) == 0){
			retval = p->int_val;
			goto done;
		}
	}
done:
	free(s);
	return retval;
}

/******************************************************************************
 * Returns the string (usually from enum) associated to the integer as defined
 * by the string_associator array.
 ******************************************************************************/
char *str_associated_to(int int_val, struct string_associator *ass)
{
	printf("%s()\n",__FUNCTION__);
	for(struct string_associator *p = ass; p->str_val != NULL; ++p){
		if(int_val == p->int_val){
			return p->str_val;
		}
	}
	return NULL;
}
