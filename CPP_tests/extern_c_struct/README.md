# Extern C struct

This demo shows that C struct definitions do not need to be enclosed within
`extern "C" { ... }` to be usable in C++ code on the contrary from function
declarations.

We can see that in `coolstruct.h` the `extern "C"` is only used for the
function declaration and not for the struct.

Functions names do get mangled by the C++ compiler so declarations of C
functions need the `extern "C"` so that the compiler produces calls to
non-mangled names.

## Struct names are not mangled

Struct names are not mangled. This is because structs do not give rise to
symbols.  Structs do not live past compilation, instead, the spirit of the
struct lives on in the offsets that the compiler used to compile field accesses
into assembler or machine code and the size of the allocations it makes on the
stack.

For example,
```
	subq	$88, %rsp
```
at the start of `main()` includes space for the declaration
```
    struct CoolStruct s;
```
and the instructions
```
	movl	$8, -32(%rbp)
	movq	$.LC0, -24(%rbp)
```
correspond to the assignments
```
    s.integer = 8;
    s.char_star = "hello";
```
so the instance of `struct CoolStruct` lives at `-32(%rbp)` and we put the value
8 at offset 0 from there, and at an offset of 8 from the beginning of the struct
we find the field `char_star`.

## Function names are mangled unless we says so

Function names do live past compilation and in C++, they are mangled.  Therefore
the declaration `int my_func();` tells the C++ compiler that a function named
`my_func` exists.  In the compiled code, this becomes `call _Z7my_funcv`.

If `my_func()` comes from C++ code, that is fine because the object file will
have the equivalent of the following assembler code:
```
_Z7my_funcv:
    # implementation
    ret
```
but if `my_func()` comes from C code, the object file will contain the equivalent
of the following assembler code:
```
my_func:
    # implementation
    ret
```

C++ provides a directive `extern "C"` to put before a declaration to tell the
the compiler that this is a declaration for a C function and that the symbol
name will not be the mangling of the function name but rather the exact function
name itself.

