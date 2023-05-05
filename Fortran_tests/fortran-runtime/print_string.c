#include <stdio.h>
#include <string.h>

void print_string(const char *str, const size_t *len)
{
    size_t size = *len+1;
    char local_str[size];
    strncpy(local_str, str, size);
    puts(local_str);
}
