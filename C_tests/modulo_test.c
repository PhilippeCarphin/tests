#include <stdlib.h>
#include <stdio.h>

/*
 * This test shows the behavior of modulo in C and possibly in most other
 * programming languages.
 *
 * It is different from the mathematical idea of remainder after division by n.
 *
 * This also shows a usual way to get the positive that maybe we wanted.  This
 * works because |-1| < 5 and wouldn't work for -6 % 5, so we could just do
 *
 *	positive_mod(int a, int n)
 *	{
 *		int tmp = a;
 *		while(tmp < 0){
 *			tmp += n;
 *		}
 *		return tmp % n;
 *	}
 *
 * But in many situations, I've needed to do this to implement some kind of
 * array traversal like
 *
 *	while(something){
 *		printf("%d\n", array[i]);
 *		i = (i - b) % n;
 *	}
 *
 * this kind of thing has come up for me where it made sense that b would never
 * be greater than n so if i is positive to begin with, we will have |i-b| < n
 * and therefore i-b+n > 0.
 *
 *	while(something){
 *		printf("%d\n", array[i]);
 *		i = (i - b + n) % n;
 *	}
 *
 * to solve the problem easily.
 *
 */

int main(void)
{
	printf("-1 mod 5 = %d\n", -1 % 5);
	printf("(-1+5) mod 5 = %d\n", (-1+5) % 5);
	return 0;
}
