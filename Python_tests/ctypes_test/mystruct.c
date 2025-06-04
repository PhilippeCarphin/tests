#include <stdlib.h>
#include <stdio.h>

struct Person {
    char *name;
    int age;
    float height;
};

void greet_person(struct Person *p){
    if(p == NULL){
        fprintf(stderr, "Hello World!\n");
        return;
    }

    fprintf(stderr, "Hello %s\n", p->name);
}
