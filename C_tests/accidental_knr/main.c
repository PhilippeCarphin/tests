#include <stdio.h>
int not_a_knr_function(); // Accidental K&R declaration
int really_not_a_knr_function(void); // New style declaration

int main(int argc, char **argv) {
    not_a_knr_function(1234); // Not an error
    really_not_a_knr_function(1234); // Compilation error : Too many arguments to function
}

int not_a_knr_function(void){
    return fprintf(stderr, "%s()\n", __func__);
}

int really_not_a_knr_function(void){
    return fprintf(stderr, "%s()\n", __func__);
}
