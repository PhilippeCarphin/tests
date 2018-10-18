#include <string.h>
#include <stdio.h>
#include "my_strlen.h"

int main(void)
{
        const char *the_string = "This is my string";
        printf("strlen(): %lu\n", strlen(the_string));
        printf("my_strlen(): %lu\n", my_strlen(the_string));

        const char *empty_string = "";
        printf("strlen(): %lu\n", strlen(empty_string));
        printf("my_strlen(): %lu\n", my_strlen(empty_string));
}
