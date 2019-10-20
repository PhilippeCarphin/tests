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
   int i = 0;
   int n = 0;
   n = (i++, i++, i++, i++, 3);
   printf("The values are i=%d,  n=%d\n", i, n);
   n = i++, i++, i++, i++, 11;
   printf("The values are i=%d,  n=%d\n", i, n);
   (n = i++), i++, i++, i++, 111;
   printf("The values are i=%d,  n=%d\n", i, n);
   return 0;
}
