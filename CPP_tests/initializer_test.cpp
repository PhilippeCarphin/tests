#include <iostream>

int main(int argc, char *argv[])
{
	bool table[5] = {true};
	for(int i = 0; i < (int)(sizeof(table)/sizeof(bool)); i++){
		std::cout << "table[" << i << "] = " << table[i] << std::endl;
	}

	bool table_2[5] = {false};
	for(int i = 0; i < (int)(sizeof(table_2)/sizeof(bool)); i++){
		std::cout << "table_2[" << i << "] = " << table_2[i] << std::endl;
	}

	std::fill(table, table + sizeof(table)/sizeof(table[0]), true);
	for(int i = 0; i < (int)(sizeof(table)/sizeof(bool)); i++){
		std::cout << "table[" << i << "] = " << table[i] << std::endl;
	}

	return 0;
}
