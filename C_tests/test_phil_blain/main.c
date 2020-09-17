#include <stdio.h>
#include <memory.h>
int recieve_array(char array[]){
    printf("%s : sizeof array is %ld\n", __PRETTY_FUNCTION__, sizeof array);
    return 0;
}
int array_experiment(int n)
{
    char string[] = "0123456789";
    printf("Sizeof string is %ld\n", sizeof string);
    recieve_array(string);
    return 0;
}
int superstitious_memset(char array[])
{
    memset(array, '\0', 11);
    sprintf(array, "Bla %s", "asdf");
    return 0;
}
int main(int argc, char **argv)
{
    array_experiment(argc);
    return 0;
}
