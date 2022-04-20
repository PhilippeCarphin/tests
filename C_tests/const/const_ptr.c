#include <stdio.h>
/*
 * assign  | modify_pointee | Declaration
 *  yes    |     yes        |    int * normal_ptr;
 *  yes    |     no         |    const int * poninter_to_const;
 *  no     |     yes        |    int * const const_pointer;
 *  no     |     no         |    const int * const const_pointer_to_const;
 *
 *  This test demonstrates that within the same scope as the declaration,
 *  violating the qualifiers causes compilation errors and that when passing
 *  things to functions, violating qualifiers only generates warnings.  In this
 *  case -Wincompatible-pointer-types-discards-qualifiers for all the lines
 *  marked '// WARNING'.
 */


int modify_pointee(int *ptr, const int * const new){
    *ptr = *new;
    return 0;
}

int modify_pointer(int ** const  ptr, const int * const new){
    *ptr = new;
    return 0;
}

int main(void)
{
    int normal_int = 7;
    int other_int = 8;
    const int const_int = 9;
    const int other_const_int = 10;

    ///////////////////////////////////////////////////////////////////////////
    //  normal_ptr;
    ///////////////////////////////////////////////////////////////////////////
    int * normal_ptr = &normal_int;
    // assignment: yes
    normal_ptr = &other_int;
    normal_ptr = &normal_int;

    // modify pointee: yes
    normal_ptr[0] = 70;
    normal_ptr[0] = 7;

    modify_pointer(&normal_ptr, &normal_int);
    modify_pointee(normal_ptr, &normal_int);

    ///////////////////////////////////////////////////////////////////////////
    //  pointer_to_const;
    ///////////////////////////////////////////////////////////////////////////
    const int * pointer_to_const = &const_int;
    // Assignement: yes
    pointer_to_const = &other_const_int;
    pointer_to_const = &const_int;

    // modify pointee: error: read-only variable is not assignable
    // pointer_to_const[0] = 70;
    // pointer_to_const[0] = 7;

    modify_pointer(&pointer_to_const, &const_int); // WARNING
    modify_pointee(pointer_to_const, &const_int); // WARNING

    ///////////////////////////////////////////////////////////////////////////
    //  const_pointer;
    ///////////////////////////////////////////////////////////////////////////
    int * const const_pointer = &normal_int;
    // assignment: error: cannot assign to variable 'const_pointer' with const-qualified type
    // const_pointer = &other_int;
    // const_pointer = &normal_int;

    // Modify pointee: Yes
    const_pointer[0] = 70;
    const_pointer[0] = 7;

    modify_pointer(&const_pointer, &normal_int); // WARNING
    modify_pointee(const_pointer, &normal_int); // OK


    ///////////////////////////////////////////////////////////////////////////
    //  const_pointer_to_const;
    ///////////////////////////////////////////////////////////////////////////
    const int * const const_pointer_to_const = &const_int;
    // assignment error: cannot assign to variable 'const_pointer_to_const' with const-qualified type
    // const_pointer_to_const = &other_const_int;
    // const_pointer_to_const = &const_int;

    // modify pointee: error: read-only variable is not assignable
    // const_pointer_to_const[0] = 70;
    // const_pointer_to_const[0] = 7;

    modify_pointer(&const_pointer_to_const, &const_int); // WARNING
    modify_pointee(const_pointer_to_const, &const_int); // WARNING

    return 0;

}
