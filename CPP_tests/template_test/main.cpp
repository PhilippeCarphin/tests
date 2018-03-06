#include "vector.h"
#include <iostream>

int main(void)
{
	Vector<int, 2> v;

	v.push_back(1);
	v.push_back(2);

	try{
		v.push_back(4);
	} catch (std::out_of_range& e) {
		std::cout << "Index out of range exception caught : " << e.what() << std::endl;
	}

	v.print();

	v.pop_back();
	v.pop_back();

	try{
		v.pop_back();
	} catch (std::out_of_range& e) {
		std::cout << "Index out of range exception caught : " << e.what() << std::endl;
	}

	return 0;
}
