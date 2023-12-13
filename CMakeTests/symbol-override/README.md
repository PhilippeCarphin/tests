We have a library `gemdyn` that uses `rpnphy`.  The final product is an
executable `main` that calls a function from `gemdyn`.

We have our original library `rpnphy` which implements `rpnphy_do_physics()`
and some other functions.

We want to override `rpnphy_do_physics()` with our own version.

For this example, the user would be given these build instructions

## Build from source

```
mkdir build
cd build
cmake .. -DUSE_OVERRIDES=[ON|OFF] -DWITH_SHADES=[ON|OFF]
make
make check
```

# Relying on the linker to handle our overrides

One approach is to create another library `rpnphy-override` that also has a
symbol `rpnphy_do_physics()`.

We set things up so that, based on the value of `USE_OVERRIDES` the linking
command for `gemdyn` will look like

```
gcc -o libgemdyn.so -shared gemdyn.o -lrpnphy-override -lrpnphy
# or
gcc -o libgemdyn.so -shared gemdyn.o -lrpnphy
```

which in CMake looks like
```cmake
if(USE_OVERRIDES)
    target_link_libraries(gemdyn PRIVATE rpnphy-override rpnphy)
else()
    target_link_libraries(gemdyn PRIVATE rpnphy)
endif()
```

This relies on details of how the linker works: it first analyzes `gemdyn.o`
and sees a bunch of symbols that it needs including `rpnphy_do_physics`, then
it looks at `-lrpnphy-override` and finds that symbol in `librpnphy-override.so`
and moves on to look at `-lrpnphy` where it finds other symbols that it needs.

It has already found `rpnphy_do_physics` so it does not take the one from `librpnphy.so`.

We will see why this is unreliable with some experiments.


# Relying on macro definitions

We create a library `rpnphy-custom` with our version of `rpnphy_do_physics` but
we name it `rpnphy_do_physics_custom`.  Now each symbol has a unique name.

In this case, we do
```C
 #ifdef USE_OVERRIDES
     rpnphy_do_physics_custom();
 #else
     rpnphy_do_physics();
 #endif
```

and our compilation command for `gemdyn.c` changes based on the value of `USE_OVERRIDES`
```
gcc -c -o gemdyn.o -DUSE_OVERRIDES gemdyn.c
# or
gcc -c -o gemdyn.o gemdyn.c
```

```cmake
target_link_libraries(gemdyn PRIVATE rpnphy-custom rpnphy)
if(USE_OVERRIDES)
    target_compile_definitions(gemdyn PRIVATE USE_OVERRIDES)
endif()
```

# Spicing things up

Suppose we decide that `main` will call a function from `rpnphy`.  Now we have
to watch out!

But let's make it even spicier: main is not going to call a function from `rpnphy`
instead it will call a function from `rpnshades` that uses a function from `rpnphy`

## Effect on linker version

What we would like is for CMake to construct the following link command
```
gcc -o main main.o -lrpnshades -lrpnphy -lgemdyn -lrpnphy-override -lrpnphy
```
Now this would in fact work:
- in `main.o` we find the symbol `main` which calls undefined symbols `gemdyn_do_a_timestep` and `rpnshades`
- in `-lrpnshades` we find the symbol `rpnshades` and get one more undefined symbol `rpnphy_do_light_polarization`
- in `-lrpnphy` we find the symbol `rpnphy_do_light_polarization` (it has other symbols but we don't know that we need them yet.
- in `-lgemdyn` we find `gemdyn_do_a_timestep` and we get an undefined symbol `rpnphy_do_physics` and `rpnphy_do_more_physics`.
- in `-lrpnphy-override` we find the symbol `rpnphy_do_physics`
- in `-lrpnphy` we find the symbol `rpnphy_do_more_physics`.

In practice however, this is not what happens.  If we are building shared
libraries, we get the following relevant summarized link commands:
- `gcc -o libgemdyn.so -shared gemdyn.o -lrpnphy-overrides -lrpnphy
- `gcc -o librpnshades.so -shared rpnshades.o -lrpnphy
- `gcc -o main main.o -lrpnpshades -lgemdyn`

Now this leads to the following output for `ldd main`:
```
linux-vdso.1
/lib64/libc.so.6
librpnshades.so
libgemdyn.so
librpnphy.so
librpnphy-overrides.so
```

Now there is a way to change the `CMakeLists.txt` so that the overrides come
before the original in the `ldd` output.  Can you find it?  Actually there are
two ways.  One of them is the right* way to do it and one is wrong.

# Experiment

With each method, we decide if `main` uses `rpnshades` or not and look at how
this affects which version of `rpnphy_do_physics` gets called by `gemdyn`:

## Linker

| `USE_OVERRIDE` | `USE_SHADES` | `rpnphy_do_physics` |
|---|---|---|
| `OFF` | `OFF` | `rpnphy_do_physics (ORIGINAL)` |
| `OFF` | `ON` | `rpnphy_do_physics (ORIGINAL)` |
| `ON` | `OFF` | `rpnphy_do_physics (OVERRIDE)` |
| `ON` | `ON` | `rpnphy_do_physics (ORIGINAL)` |

We see that when the user requests the overrides, if they also request `WITH_SHADES`,
this disables the override!

## Defines

| `USE_OVERRIDE` | `USE_SHADES` | `rpnphy_do_physics` |
|---|---|---|
| `OFF` | `OFF` | `rpnphy_do_physics (ORIGINAL)` |
| `OFF` | `ON` | `rpnphy_do_physics (ORIGINAL)` |
| `ON` | `OFF` | `rpnphy_do_physics_custom (CUSTOM)` |
| `ON` | `ON` | `rpnphy_do_physics_custom (CUSTOM)` |

We see that if we request the overrides, the actual code itself calls a function
that has a different name.  No linker trickery can happen!

# Attempting to fix the linker version

## Ordering

The shades thing changes what function is called by `gemdyn` because the
`target_link_libraries(main rpnshades)` came before `target_link_libraries(gemdyn)`
so we could be tempted to say "Oh I'll just exchange those two lines to get:

```cmake
target_link_libraries(main PRIVATE gemdyn)
if(WITH_SHADES)
    target_compile_definitions(main PRIVATE WITH_SHADES)
    target_link_libraries(main PRIVATE rpnshades)
endif()
```
and go home".

That would indeed fix the linker version.  However I will advise against that.

1. Did you notice that you could do that?
2. What if this was a more complex project?

Instead of having main link with `rpnphy` directly, I invented a third library
`rpnshades` that links with `rpnphy`.  But I gave it away earlier because I
explicitely told you that `rpnshades` uses `rpnphy`.  In practice, the author
does not create a problem on purpose and give us hints about the solution.

## The bad version

One way one could think of solving the problem is saying "I know there's some
kind of thing with linkers and the order of libraries.  Maybe something's happening
that inserts `-lrpnphy` to appear before `-lrpnphy-override` some how (imagine
a way more complex project where `main` links with A,B,C,D and they each link with other libraries).  I know, I'm gonna put `-lrpnphy-overrides` right there as the very first link library of `main`.  That way I know that nothing is going to come
before it.

```cmake
add_library(main main.c)
target_link_libraries(main PRIVATE rpnphy-override)
# ...
if(WITH_SHADES)
    target_compile_definitions(main PRIVATE WITH_SHADES)
    target_link_libraries(main PRIVATE rpnshades)
endif()
target_link_libraries(main PRIVATE gemdyn)
```

## Conclusion

While it is possible to get some kind of overriding behavior happening by changing
putting the library with the overrides before the overriden library in the link
order, this approach is not recommended.


# DRY and the defines method

In the example, I placed defines where `rpnphy_do_physics` is called.  If such
a function is called in a whole bunch of places

