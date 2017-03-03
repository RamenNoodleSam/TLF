#include <iostream>
#include "Core.h"

int main(int argc, char **argv){
	try {
		Core core;
		return core.run();
	}
	//catch any serious runtime exceptions in the Core code
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return 0;
	}
}