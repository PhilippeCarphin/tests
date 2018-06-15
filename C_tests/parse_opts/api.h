#ifndef _MY_MAIN_H
#define _MY_MAIN_H
struct MyOpts;
int my_main(struct MyOpts *opts);
enum Command { SECOND_CMD, FIRST_CMD, };
struct MyOpts {
   enum Command cmd;
   char *a_path;
   int a_flag;
   float float_param;
   int nb_elements;
   char **elements;
};
#endif
