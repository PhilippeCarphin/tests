#include <stdlib.h>
#include <stdio.h>

void *echo_void_star(unsigned long int x){
  return (void*)x;
}

int *echo_int(int x){
  if(x == 666){
    return NULL;
  }
  int *x_ptr = malloc(sizeof *x_ptr);
  *x_ptr = x;
  return x_ptr;
}

struct MyThing {
  int integer;
  void * void_star;
};

struct MyThing *MyThing_New(int integer, void* void_star){
  if(integer == 666){
    return NULL;
  }
  struct MyThing *mt = malloc(sizeof *mt);
  mt->integer = integer;
  mt->void_star = void_star;
  return mt;
}
