
#include <iostream>
#include <string>

int main()
{
	std::cout << "Test\n";

	std::system("dir");
	std::system("7Zip\\7z a testArchive \"test2.txt\"");
	return 0;
}