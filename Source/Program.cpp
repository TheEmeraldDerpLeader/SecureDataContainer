
#include <iostream>
#include <string>
#include "SDCSoftware.hpp"

int main()
{
	std::cout << "Test\n";

	std::system("dir");
	std::system("7Zip\\7z a testArchive \"test2.txt\"");


	SDCSoftware startUI;
	startUI.CommandInterfaceStart();

	return 0;
}