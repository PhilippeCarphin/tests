#include <stdio.h>

int print_string(char *s){
    s[3] = 'Z';
    printf("String : %s\n", s);
    return 0;
}

int modify_pointer(char **s_ptr){
    static char new_str[] = "This is a new string";
    *s_ptr = new_str;
    return 0;
}

int main(void){

    char string[] = "This is my string";

    const char * const_ptr = string;
    char * const ptr_const = string;

    // By going through a function, we can do whatever we want
    print_string(const_ptr);
    print_string(ptr_const);

    modify_pointer(&const_ptr);
    modify_pointer(&ptr_const);

    // const_ptr[8] = 'A';

    ptr_const[9] = 'B';

    printf("String '%s'\n", string);

    return 0;

}
