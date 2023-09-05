#include "coolstruct.h"
#include "coolclass.h"

int main(int argc, char **argv)
{
    struct CoolStruct s;
    s.integer = 8;
    s.char_star = "hello";

    print_cool_struct(&s);

    CoolClass c;
    c.integer = -1;
    c.string = "goodbye";

    c.print();
    return 0;
}
