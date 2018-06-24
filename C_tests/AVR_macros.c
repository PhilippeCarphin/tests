#include <stdio.h>
#include <stdlib.h>

/*
 * This test looks into how the macros PORTA, PORTB, etc work on AVR-libc
 *
 * they have macros for registers like PORTA.  It is something like
 * #define PORTA = *0xABCD
 * where 0xABCD is an actual address.
 *
 * Let's look for avr/io.h and see if we can understand how it all works.
 */


/*
 * IN io.h,
 *
 * There is an #if-#elif-#endif chain that includes the right H file, which in
 * our case is avr/iom324pa.h and it contains the line
 *
 * #define PORTA  _SFR_IO8(0x02)
 *
 * And back in avr/sfr_defs.h, (by grepping for '#define _SFR_IO8') we find:
 *
 * sfr_defs.h:152:#define _SFR_IO8(io_addr) ((io_addr) + __SFR_OFFSET)
 * sfr_defs.h:179:#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + * __SFR_OFFSET)
 *
 * An analysis of sfr_defs.h reveals that the second one is the one that is used
 * when I do my projet1(poly) stuff.
 *
 * Now, looking up the _MMIO_BYTE, we (by grepping for '#define _MMIO_BYTE')
 * find
 *
 * sfr_defs.h:128:#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
 *
 * so it takes a memory address mem_addr and casts it to volatile uint8_t *.
 * And it adds a star in front of it.
 *
 * To resume, when you type PORTA, the preprocessor sees this and replaces it
 * with the macro's value, which is another macro that needs to be evaluated
 * etc.
 *
 * PORTA -> _SFR_IO8(0x02)
 *       -> _MMIO_BYTE((0x02) + __SFR_OFFSET)
 *       -> *( (volatile uint8_t *) ((0x02 + __SFR_OFFSET)) )
 *          -  --------------------------------------------
 *          |         a litteral memory
 *         star        address cast to
 *                    volatile uint8_t *
 *
 * THE THING TO REMEMBER is that PORTA expands to "star + the address of a
 * uint8_t".
 *
 * I actually think it would be even simpler if porta WAS just the address.
 * Then there wouldn't be the need for me to launch into hard to follow
 * conversations with students who want to pass a port to a function and don't
 * understand why they can't get it to work.
 *
 * If we had the macro PORTA_PTR, then we would do *PORTA_PTR |= (1 << 6) and
 * things like that, we would understand that what PORTA is is a SPECIFIC
 * address in memory that is hardcoded and dependant on the particular chip.
 *
 * We wouldn't have conceptual hurdles when passing it to functions because it's
 * just an address, purely a value of a certain type, as opposed to a
 * dereferenced pointer.
 *
 * You can't say that about PORTA, it is not just a value.  It is not the value
 * at a certain address, it is (the value at a certain address), it is the
 * address AND the act of taking the value at that address.
 *
 * This is why I think that PORTA_PTR is easier to understand than PORTA for
 * beginners.
 *
 * For more advanced users, the macro PORTA is a neat trick to enable neat
 * syntax like
 *
 *    PORTA = 8;
 *
 *    if(PORTA & (1 << 5)){ ...
 *
 * without constantly having to write the '*' that would be required for
 * PORTA_PTR.  And for an advanced user, it's easy to understand that to pass a
 * port to a function, you just declare a function that takes a
 *
 *    volatile uint8_t *
 *
 * and you pass it &PORTA which is PORTA_PTR.
 */


 /* HERE I REPRODUCE WHAT AVR-libc DOES */

/*
 * Pretend that the __SFR_OFFSET that I saw while analysing the avr header files
 * represents the start of the memory address range that is mapped to the
 * registers.
 */
#define __SFR_OFFSET &registers

/*
 * Copy exactly the stuff found while analysing headers adapted to 4 byte
 * integers.
 */
#define _MMIO_DWORD(mem_addr) (*(volatile int *)(mem_addr))
#define _SFR_IO32(io_addr) _MMIO_DWORD((io_addr) + __SFR_OFFSET)
#define PORTA _SFR_IO32(4)
#define PORTB _SFR_IO32(8)

#define PORTA0 0
#define PORTA1 1
#define PORTA2 2
#define PORTA3 3
#define PORTA4 4
#define PORTA5 5
#define PORTA6 6
#define PORTA7 7

/*
 * This represents the registers of our AVR chip.  This wouldn't be in an actual
 * avr program because this memory wouldn't be allocated by declaring a
 * variable, it would be allocated by virtue of the fact that that is where the
 * registers are.
 */
int registers[30];

/*
 * I have a function that takes the address of an int, and does something to the
 * int at that address.
 */
typedef volatile int * reg_ptr;
void set_pins(reg_ptr p, int pins)
{
	*p |= pins;
}

void clear_pins(reg_ptr p, int pins)
{
	*p &= ~pins;
}

int main()
{
   /*
    * Set the thing at the adress of an int to 0.
    */
	PORTA = 0;
	PORTB = 0;

   /*
    * To the function set_pins, we are passing &PORTX which is
    * the adress of (the thing at the address of an int)
    */
	set_pins(&PORTA, (1 << PORTA2)|(1 << PORTA1)|(1 << PORTA0));
	set_pins(&PORTB, (1 << PORTA7)|(1 << PORTA6)|(1 << PORTA5));

   /*
    * Print the thing at the address of an int
    */
	printf("new value of PORTA : %d\n", PORTA);
	printf("new value of PORTB : %d\n", PORTB);
	return 0;
}

