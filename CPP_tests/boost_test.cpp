/* Tue Mar  7 13:37:09 EST 2017
 * This test documents installation of boost libraries on MAC OS
 * using the command
 * $ brew install boost
 * The test passed: This program was compiled using the command
 * $ g++ -I /usr/local/Cellar/boost/1.63.0/include boost_test.cpp
 * and running ./a.out 
 */
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

int main()
{
	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;

	std::cout << "This program multiplies numbers by three" << std::endl << "Enter Number > ";
	std::for_each( in(std::cin), in(), std::cout << (_1 * 3) << "\nEnter number > " );
}
