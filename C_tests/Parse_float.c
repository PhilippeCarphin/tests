#include "debug.h"

/********************************************************************************
 * Reads the string of a floating point number into two integers, one for the
 * whole part and one for the decimal part) and a floating point value.
 *
 * Made for use in string parsing.  Increments a cursor as it reads.
********************************************************************************/
int read_float(int *whole_part, int *decimal_part, float *float_value, char **cursor_ptr)
{
	int wp = 0;
	int fp = 0;
	int sign = 1;
	int digits = 0;
	float float_fp;
	char c;

	/*
	 * Read the digits and possible minus sign into an integer
	 * until we hit '.' or a ' '.
	 */
	while( (c = *(*cursor_ptr)++) ){
		if('0' <= c && c <= '9'){
			wp *= 10;
			wp += (c - '0');
		} else if( c == '-' ){
			sign = -1;
		} else if( c == '.'){
			break;
		} else if( c == ' '){
			goto done_parsing;
		}
	}

	/*
	 * Read the subsequent digits into another integer.
	 * Also count the digits in order to compute a floating point value
	 */
	while( (c = *(*cursor_ptr)++) ){
		if('0' <= c && c <= '9'){
			fp *= 10;
			fp += (c - '0');
			++digits;
		} else if(c == ' '){
			break;
		}
	}

	/*
	 * Put the integer after the '.' into a float and divide by 10 as many times
	 * as there are digits in the integer.
	 */
	float_fp = fp;
	while( digits-- )
		float_fp /= 10;

done_parsing:
	/*
	 * Assign the values to the out_parameters
	 */
	*whole_part = wp * sign;
	*decimal_part = fp;
	if(wp == 0){
		*decimal_part *= -1;
	}

	*float_value = sign * (wp + float_fp);
err:
	return 0;
}
/********************************************************************************
 * Testing the function.
********************************************************************************/
#define TEST_PASSED {printf("Test passed\n");}
#define TEST_FAILED {printf("TEST_FAILED\n"); exit(1);}
int main(int argc, char **argv)
{
	printf("Testing g-code interpreter library\n");

	char float_str[10] = "-17.7 -0.1";
	int whole_part;
	int fractionnal_part;
	float float_value;
	char *cursor = float_str;
	read_float(&whole_part, &fractionnal_part, &float_value, &cursor);
	if(whole_part == -17 && fractionnal_part == 7){
		IVAL(whole_part);
		IVAL(fractionnal_part);
		VARVALUE(float_value,%f);
		TEST_PASSED
	} else {
		IVAL(whole_part);
		TEST_FAILED
	}

	read_float(&whole_part, &fractionnal_part, &float_value, &cursor);
	if(whole_part == 0 && fractionnal_part == -1){
		IVAL(whole_part);
		IVAL(fractionnal_part);
		VARVALUE(float_value,%f);
		TEST_PASSED
	} else {
		TEST_FAILED
	}
