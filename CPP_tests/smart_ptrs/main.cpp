#include <iostream>
#include <memory>

std::shared_ptr<int> my_function(std::shared_ptr<int> p)
{
	std::cout << "Function" << __FUNCTION__ << std::endl;
	std::cout << "p.use_count() " << p.use_count() << std::endl;
	return p;

}

void unique_function(std::unique_ptr<int> p)
{
	std::cout << "Function" << __FUNCTION__ << std::endl;
	std::cout << "p.get() " << p.get() << std::endl;
}

int main(int argc, char **argv)
{
	std::cout << "Function" << std::endl;
	std::shared_ptr<int> s_ptr(new int);
	int *int_ptr = s_ptr.get();
	*s_ptr = 8;
	my_function(my_function(s_ptr));
	std::cout << "*int_ptr " << *int_ptr << std::endl;
	std::cout << "s_ptr.use_count() " << s_ptr.use_count() << std::endl;


	std::unique_ptr<int> u_ptr(new int[8]);

	// Calling this function causes a compiler error but otherwise it compiles
	// unique_function(u_ptr);


	return 0;
}
