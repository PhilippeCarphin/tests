#include <stdio.h>
#include <string.h>

int main(void){
        char str1[] = "premiere chaine";
        char str2[] = "deuxieme chaine";

        if(strcmp(str1, str2) == 0){
                printf("Les chaines sont egales");
        } else {
                printf("Les chaines sont differentes");
        }
}
