#include <cstddef>
#include <stdexcept>
#include <iostream>

/*******************************************************************************
 * Basic fixed size stack used to illustrate having an integral type as a
 * template parameter.
*******************************************************************************/
template<class C, int SIZE>
class Vector{
	public:
		void push_back(C c);
		C pop_back();
		void print();

	private:
		C storage[SIZE];
		int top = 0;
};

/*******************************************************************************
 * Defining a function for a template class having an int parameter
 * This is a push function.  It uses the SIZE as if it was an attribute of the
 * class.
*******************************************************************************/
template<class C, int SIZE>
void Vector<C, SIZE>::push_back(C c)
{
	if(top == SIZE){
		throw std::out_of_range("Push into full vector");
	}
	storage[top++] = c;
}

/*******************************************************************************
 *
*******************************************************************************/
template<class C, int SIZE>
C Vector<C, SIZE>::pop_back()
{
	if(top == 0){
		throw std::out_of_range("Pop from empty vector");
	}
	return storage[--top];
}

/*******************************************************************************
 *
*******************************************************************************/
template<class C, int SIZE>
void Vector<C, SIZE>::print()
{
	std::cout << "Print stack" << top << std::endl;;
	if(top != 0){
		std::cout << "  " << storage[top-1] << "<-- top";
	}
	for(int i = top; i;){
		std::cout << "  " << storage[--i] << std::endl;
	}
}

