# Undefined exit code

When main is declared as returning void, we may get a surprising exit code from
our program.

This is because the code that calls our `main` expects a return value and uses
that for the process exit code.

Compilers know about this and may have `main` return 0 even if we don't return
a value in our code.

GCC does this but not if we declare main as returning void.

It is general knowledge that the register `eax` is used to pass return values
of functions returning `int`.  The called function places its return value in
`eax` and the caller looks in `eax` to get the return value.

Therefore, if we do something that manipulates `eax` in our main function, we
can expect the code that calls main to use whatever is in `eax` as the return
value of `main` and as the exit code of the process.

All of this is going to be compiler dependant.

## Nothing

With an empty main function, I get the exit code of 54.  This just means that
the last thing that was put in `eax` was 54 but I don't know where this comes
from.

## Assigning a variable to a variable

With
```
int y = 88;
int x = 12;
```
The `eax` register is used to transfer the value of one variable to the other.
```
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
```
The value in question is 12 and this is the exit code of our process.


## For loop

A for loop where the limit is a variable.
```
x = 27;
for(int i = 0; i<x ; i+=2){
    ;
}
```
We store the iteration variable in eax and compare it with the variable x
```
	movl	$27, -12(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
	addl	$2, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
```
With this we get an exit code of 28 which is the last value that was placed in
eax.

### For loop where the limit is hard coded

```
int x = 12;
int y = 88;
y = x;

for(int i = 0; i<27 ; i+=2){
    ;
}
```

```
	movl	$0, -4(%rbp)
	jmp	.L2
	addl	$2, -4(%rbp)
	cmpl	$26, -4(%rbp)
	jle	.L3
```
with this we get an exit code of 12 because of the `y = x` and the for loop
operates only on memory. 
