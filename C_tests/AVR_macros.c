#include <stdio.h>
#include <stdlib.h>

/*
 * This test looks into a theory that I have about the register macros used for
 * the register.
 *
 * they have macros for registers like PORTA.  It is something like
 * #define PORTA = *0xABCD
 * where 0xABCD is an actual address.
 */

int porta = 5;
int portb = 5;

#define PORTA *(&porta)
#define PORTB *(&portb)

#define p0 1
#define p1 2
#define p2 4
#define p3 8
#define p4 16
#define p5 32
#define p6 64
#define p7 128

void set_pins(int *p, int pins)
{
	*p |= pins;
}

void clear_pins(int *p, int pins)
{
	*p &= ~pins;
}

int main()
{
	function_1(reg_ptr);
	PORTA = 0;
	PORTB = 0;
	set_pins(&PORTA, p2|p1|p0);
	set_pins(&PORTB, p7|p6|p5);
	printf("new value of PORTA : %d\n", PORTA);
	printf("new value of PORTB : %d\n", PORTB);
	return 0;
}

