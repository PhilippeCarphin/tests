
#include <string.h>

void print_string(const char *str, const size_t *len);

int main(int argc, char **argv)
{
    for(int i = 0; i < argc; i++){
        size_t len = strlen(argv[i]);
        print_string(argv[i], &len);
    }
    return 0;
}
