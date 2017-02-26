#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ps printf("switch_args:%s\n",switch_args)
int main ( int argc , char ** argv ) {

   const char *switch_args = "switch_1=80,switch_2=101,gen_switch=Obama";

   ps;
   switch_args = strstr(switch_args,",")+1;
   ps;
   switch_args = strstr(switch_args,",")+1;
   ps;
   return 0;
}
