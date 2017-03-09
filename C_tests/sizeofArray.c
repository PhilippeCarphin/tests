/* This is because I started using cppcheck, which is supposed to work for C and
 * C++.  It warns me that passing an array as a function argument to sizeof
 * would return the size of a pointer.
 *
 * Also, see the test in array_diff_pointer where it is explained that when an
 * array is passed to a function, the array identifier is converted to a
 * pointer.  That test shows that it makes a difference.
 *
 * NVM I get it, it's when I pass the array to a function, and you do sizeof
 * that it gives the size of a pointer.  The reason is that sizeof is acutally
 * resolved at compile time.  When the array declaration is in the scope of the
 * "call" to sizeof, then the compiler can know what size the array has but when
 * it's not, then too bad.
 *
 * This is true even when the array size is given in the function delcaration.
 * As I have tested, the compiler doesn't seem to give a shit about the size of
 * the array being passed so the array size given in the function declaration is
 * just a waste of characters, and you might as well just use 'char *' so that
 * you don't fool yourself into thingking that 'char param[]' makes any
 * difference.
 *
 * Another thing to check out is old-school C function definitions, and these
 * don't work either.
 *
 * Another thing I want to check out is variable sized arrays. The test with
 * various calls to var_sized_array(size_t array_size) show that we do in fact
 * get the array size.  It also shows that there is more than compile time
 * substitution going on.  Even if we suspect that the compiler can figure out
 * the size from the call var_sized_array(1234) at compile time because of the
 * integer litteral constant, the following calls using a user-entered char
 * prove that sizeof is resolved at runtime.
 *
 * */




#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE 1000
#define HALF_ARRAY_SIZE 500

/*******************************************************************************
 * For variable sized arrays, as long as the declaration is in the same scope,
 * the sizeof operator will give the right value.
*******************************************************************************/
int var_sized_array( size_t array_size )
{
   int var_array[array_size];
   printf("       var_sized_array() :   sizeof var_array : %lu\n",
                                                   sizeof var_array);
}

/*******************************************************************************
 * Even using an old school C declaration will not help us here.
*******************************************************************************/
int printSize_oldSchool( param_array )
   int param_array[ARRAY_SIZE];
{
   printf("   printSize_oldSchool() : sizeof param_array : %lu\n",
                                                   sizeof param_array);
}


/*******************************************************************************
 * This test shows that passing an array to a function makes it's size
 * unavailable through sizeof.  More precisely, the function receives a pointer
 * and therefore we get the size of a pointer.
*******************************************************************************/
int printSize( int param_array[])
{
   printf("             printSize() : sizeof param_array : %lu\n",
                                                   sizeof param_array);
}

/*******************************************************************************
 * This function shows that even if we have the array size in the function
 * parameters, that still doesn't do anything.
*******************************************************************************/
int printSize_sizeDeclared( int param_array[ARRAY_SIZE])
{
   printf("printSize_sizeDeclared() : sizeof param_array : %lu\n",
                                                   sizeof param_array);
}

/*******************************************************************************
 * This test shows that we can use the sizeof operator on member arrays of
 * structs because the compiler always has access to it's declaration.
 *
 * Note that the first commented line in this function shows that we need an
 * instance of that struct to request the size of one of it's members.  I don't
 * know if there is a way of getting the size of a member without having an
 * instance but I have not looked into it.
*******************************************************************************/
struct MyArray{
	int inner_array[20];
};
int print_struct_sizeof()
{
	// printf("%s(): Sizeof struct member array is %lu\n",
	//                                   __func__, sizeof(MyArray.inner_array));

	struct MyArray ma;
	printf("%s(): Sizeof struct member array is %lu\n",
			                                 __func__, sizeof(ma.inner_array));
	return 0;
}

int main ( int argc , char ** argv ) {

   int my_array[ARRAY_SIZE];
   int half_my_array[HALF_ARRAY_SIZE];

   printf("                In scope : sizeof my_array : %lu\n", sizeof my_array);

   printf("\n");

   printSize(my_array);
   printf("\n");
   printSize_sizeDeclared(my_array);
   printSize_sizeDeclared(half_my_array);
   printf("\n");
   printSize_oldSchool(my_array);
   var_sized_array(1234);
   char c = getchar();
   var_sized_array((size_t)c);
   print_struct_sizeof();

   return 0;
}
