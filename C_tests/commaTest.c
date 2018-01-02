#include <string.h>
#include <stdio.h>
/*
 * This test demonstrates the use of the comma operator.  It is useful for
 * making complex for loops like
 *
 * u32 s_i,s_j; // coordinates in the screen
 * u32 b_i, b_j; // coordinates in the bitmap
 * for( s_i = screen_top    , b_i = img_top; s_i < screen.h  && b_i < img_bottom; ++s_i, ++b_i)
 * {
 *     	for(s_j = screen_left, b_j = img_left; s_j < screen.w  && b_j < img_right ; ++s_j, ++b_j)
 *     	{
 *     	    // Image pixel (b_i,b_j) ---> screen pixel (s_i,s_j)
 *     	    if(set_pixel_rgba(s_i,s_j,get_pixel_rgba(b_i,b_j,bmp,data))) return -1;
 *     	}
 * }
 * return 0;
 *
 * One other thing is to save lines of code, I've seen it in the linux kernel
 * and that's how I learned about it.  I saw it where it could just have been a
 * semicolon.
 *
 */

int f(int arg)
{
	printf("%s(%d) \n", __func__, arg);
	return arg;
}

int main ( int argc, char* argv[]){

   int a;
   printf ("Commas are wack (a = 4, a += 3) -> %d \n", (a=4, a+=3));

   printf("It executes the statements from left to right "
		  "and returns the result of the last statement\n");

   printf("Doing (f(1), f(2), f(3)) -> %d \n", (f(1), f(2), f(3)));

   return 0;
}
