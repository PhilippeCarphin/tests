#include <stdio.h>
#include "api.h"
#include "options.h"

/*
 * Responsible for turning parsed command line arguments into internal program
 * function calls
 */
int first_subroutine(struct MyOpts *opts);
int second_subroutine(struct MyOpts *opts);
int my_main(struct MyOpts *opts){
   //...
   (void) opts;
   return 0;
}

int first_subroutine(struct MyOpts *opts){
   (void) opts;
   return 0;
};

int second_subroutine(struct MyOpts *opts){
   (void) opts;
   return 0;
};
