#include "Errors.h"
#include <iostream>


void FatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	exit(1);
}
