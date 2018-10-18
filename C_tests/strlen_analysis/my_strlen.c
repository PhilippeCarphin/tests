#include <stdlib.h>

int my_strlen(const char *str){
        const char *s = str;
        while(*++s!= 0);
        return s - str;
}
