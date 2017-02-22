#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long int other_array[];
extern unsigned long int *bad_array;
unsigned long int *p;
int pause()
{
	printf("Press ENTER to continue ... ");
	getchar();
	system("clear");
	puts("====================================================================\n");
	putchar('\n');
}
int main(int argc, char **argv)
{
	int i = 0;
	for(i = 0; i < 10; ++i)
	{
		printf("other_array[i] = %d ", other_array[i]);
	}putchar('\n');

	system("clear");
	puts("===================================================================\n");
	printf("If we think about it, there's a way of easily seeing that there is\n"
			"a difference between an array identifier and pointer.\n"
			"Let's say I have an array\n\n"

			"\tint arr[5];\n\n");
	int arr[5];
	int *ptr = &(arr[0]);
	printf("What is the address of arr?\n"
			"Well let's print it\n\n");
	pause();
	printf("\t   &arr = %p\n\n",arr);
	printf("\t    arr = %p\n\n",arr);
	printf("\t&arr[0] = %p\n\n",&(arr[0]));
	printf("And there you have it, the identifier arr lives at the address that\n"
			"it contains but that's weird right, but the thing is that it does\n"
			"not contain an address, it's just something that the compiler does\n"
			"to let us use the array identifier as if it were a pointer to the\n"
			"first element of the array.\n\n");
	pause();

	printf("\t     arr = %p\n\n",arr);
	printf("What if we do this with a pointer?\n\n"
		   "\tint *ptr = arr;\n\n");
	printf("\t    &ptr = %p\n\n",&ptr);
	printf("\t     ptr = %p\n\n",ptr);
	printf("This shows that the compiler must do different things when it is dealing\n"
			"with an array identifier and a pointer.\n\n");
	pause();

	printf(	"The reason that this doesn't cause problems is that the compiler does\n"
			"what's right by evaluating arr as &arr which is what happened here\n"
			"and it did this because it knew that arr was an array and not a pointer\n"
			"And it's hard to trick the compiler by say passing our array to a\n"
			"function because the compiler passes &arr to the function, so the\n"
			"function gets a pointer pointing to &(arr[0]) which is the behavior\n"
			"we are all used to.\n\n");

	printf("The point is that the identifier LIVES AT &arr[0], which means that\n"
			"there is one step less when accessing arr[i] than when accessing ptr[i]\n\n");

	pause();
	printf(
			"In the first case, you have a symbol arr, you look where it lives.\n"
			"It lives at address X, you add i*sizeof(int) to that to get Y and you\n"
			"look at *Y which is the integer arr[i]\n\n"

			"NOW, what happens when we look at ptr[i]?  Well, we need to look at\n"
			"where the symbol ptr lives.  It lives at address U, we get *U, that's\n"
			"the address of the first element of the array, call it V.  Next we\n"
			"add i*sizeof(int) to that to get W.  And finally, *W is the integer\n"
			"that we wanted.\n\n"

			"Now the compiler does the right thing for us, but we can trick it\n"
			"which I will do for you now.\n\n");
	pause();
	printf(
			"We have two global arrays in other_file.c which I have given myself\n"
			"access to in main.c by using the keyword extern.  However, for \n"
			"bad_array, I have obscured the fact that the referrence symbol\n"
			"bad_array is an array.  The compiler will do the U->V->W->*W thing\n"
			"instead of the X->Y->*Y thing to get my integer.\n\n"

			"First let us look at where the things really are by asking our other\n"
			"file to tell us\n\n");

	other_function();

	printf("These are the values that we get in %s\n\n",__FILE__);
	printf("\t%s :          bad_array = %p\n", __FILE__, bad_array);
	printf("\t%s :    &(bad_array[0]) = %p\n\n", __FILE__, &(bad_array[0]));
	printf("\t%s :         &bad_array = %p\n", __FILE__, &bad_array);
	/*
	 * This line causes a segmentation fault
	 */
	/* printf("\t%s :       bad_array[0] = %ld", __FILE__, bad_array[0]); */

	printf("We see that the compiler was fooled by our misuse of the external\n"
			"symbol declaration mechanism. So if I asked for bad_array[i], it\n"
			"look where the symbol bad_array lives\n\n");
	printf("\t%s :         &bad_array = %p\n", __FILE__, &bad_array);
	printf("Then it looks at what is in memory there (the value of the pointer\n"
			"because it thinks we have a pointer");
	printf("\t%s :         *bad_array = %p\n", __FILE__, *((char *)bad_array));

	printf("When we have a pointer, it lives somewhere\n\n");
	printf("\tAddress of p    : %p\n\n",&p);
	printf("We assign it a value maybe by doing a malloc\n\n");
	p = malloc(40*sizeof(unsigned long int));
	printf("\tcontent of p    : %p\n\n",p);
	p[0] = 0;
	p[1] = 11;
	p[2] = 22;
	p[3] = 33;
	p[4] = 44;
	printf("\taddress of p[0] : %p\n\n",&(p[0]));
	return 0;
}



