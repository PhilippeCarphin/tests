# Transitivity with static and shared libraries

Consider the situation with two libraries and an executable.

```
(exec:main) -> (lib:dotproduct) -> (lib:multiply)
     E                 B                 A
```

This test demonstrates that with static libraries, it is necessary to have both
A and B in the linking command, and that with shared libraries, if B is linked
with A, then only B needs to be in E's link command (the linker still needs
to be able to find A in that case.

We also look at how CMake handles this transitive dependency.
# Makefile
## Less ideal shared linking
```
cc -shared -o libmultiply.so multiply.o
cc -shared -o libdotproduct.so dotproduct.o
cc -o main 
main.o -L. -ldotproduct -lmultiply
```
## Ideal shared linking
Here we link `libdotproduct.so` with the `-lmultiply` flag.
```
cc -shared -o libmultiply.so multiply.o
cc -shared -o libdotproduct.so dotproduct.o -L. -lmultiply
cc -o main 
main.o -L. -ldotproduct
```
## Static linking
```
ar -crs libdotproduct.a dotproduct.o
ar -crs libmultiply.a multiply.o
cc -o main_static main.o -L. -ldotproduct -lmultiply
```
```
000000000040081b T multiply
0000000000400715 T dot_product
```

## CMake
To make sure that something was needed, I had to be able to remove it and see
if there were errors.  Because I couldn't tell CMake to do things the wrong
way, I have a makefile to test things that don't work to confirm they don't work.

Everything is run from a build directory contained in the source directory.

Note
```
target_link_libraries(dotproduct PRIVATE multiply)
```
which says that dotproduct "uses" multiply but people who use dotproduct don't
need multiply.

### Shared

```
cmake .. -DBUILD_SHARED_LIBS=OFF
make VERBOSE=1
```

In the link command for `main`, we only see `libdotproduct.so`.

And in the link command for `libdotproduct.so` we see `libmultiply.so`.

This is as expected considering we used `PRIVATE` in our `target_link_libraries`
command.

```
 Properties for TARGET dotproduct:
   dotproduct.INTERFACE_LINK_LIBRARIES = <NOTFOUND>
   dotproduct.LINK_LIBRARIES = "multiply"
 Properties for TARGET main:
   main.INTERFACE_LINK_LIBRARIES = <NOTFOUND>
   main.LINK_LIBRARIES = "dotproduct"
```

### Static

I expected this to fail if building statically because `libmultiply.a` would
not be on `main`'s link command and that I would have to change the `PRIVATE`
to `PUBLIC` in `target_link_libaries(dotproduct PRIVATE public)`.

```
cmake .. -DBUILD_SHARED_LIBS=OFF
make VERBOSE=1
```
Sruprisingly, we see `libmultiply.a` in the link command for the executable.

Now looking at the properties, we see
```
 Properties for TARGET dotproduct:
    dotproduct.INTERFACE_LINK_LIBRARIES = "$<LINK_ONLY:multiply>"
```




