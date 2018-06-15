/* And a main function whose job it is to get the command line argumnets, turn
 * them into a struct MyOpts and dispatch to the right command*/
#include "api.h"
#include "options.h"
int main(int argc, char * argv[])
{
   struct MyOpts *opts;

   if(parse_args(argc, argv, &opts)){
      return -1;
   }

   return my_main(opts);
}
