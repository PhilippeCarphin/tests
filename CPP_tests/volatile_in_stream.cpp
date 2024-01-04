#include <iostream>
#include <stdio.h>

/*
 * This test demonstrates that volatile changes the type of 
 * the variable 's' in such a way that the chosen overload of
 * cout::operator<< is not what one would expect.
 *
 * A commenter on this video https://youtu.be/zGWj7Qo_POY?si=kgaohBCTbt0qS2xI
 * showing the wierdest syntax quirks of C++ added this code and I had to try {
 * it out.
 *
 * The commenter said that '1' gets printed for s and although he didn't explain
 * why, he was right.
 */

int main() {

  volatile char const * s = "Hello, world!";

  std::cout << "s = '" << s << "'" << std::endl; // Outputs `s = '1'`

  fprintf(stderr, "s = '%s'\n", s); //

  return 0;
}
