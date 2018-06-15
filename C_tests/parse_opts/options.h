#ifndef  _OPTIONS_H
#define _OPTIONS_H
/*
 * FIRST : Decide what your options are
 */
struct MyOpts;
int parse_args(int argc, char *argv[], struct MyOpts **opts);
#endif
