// #include <iostream>
#include <stdio.h>

int main(void)
{
    // EICRA = '(PIND & 0x04)';

    auto long_char = '(PIND & 0x04)';
    char *ptr = (char *)&long_char;

    char actual_char = (char)long_char;

    // std::cout << "'(PIND & 0x04)' evaluates to " << actual_char << std::endl;
    printf("'(PIND & 0x04)' evaluates to '%c'\n", actual_char);

    // std::cout << "The bytes of long_char are as follows" <<std::endl;

    for(unsigned int i = 0; i < 8; i++){
        // std::cout << "ptr[" << i << "] = " << ptr[i] << std::endl;
        printf("The ptr[%u] = %c\n", i, ptr[i]);
    }

}
