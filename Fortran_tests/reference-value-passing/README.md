This code looks at what happens when we pass something to a Fortran when the
argument is marked with VALUE or not.

```C
DateTimeVal(%ld) 11512092260
DateTimeRef(%ld) 140736384707216
*(time_t*)DateTimeRef(%ld) 11512092260
```


The value is 11512092260 which is what is expected since that is what we set the
integer to in `main.f90`.

The second argument was passed by reference so our `time_t` actually contains
the address of a `time_t`.

If we interpret it as a `time_t *` and then dereference it, we get the same
value as the second argument which is what we expected because the call in
the Fortran code passed the address of the integer to the function.

