#include "callback.h"
#include <iostream>
#include <string>

void fct1(int arg1, const std::string & arg2)
{
	std::cout << "fct 1 " << arg1 << " " << arg2 << std::endl;
}

void fct2(const std::string & arg2)
{
	std::cout << "fct 2 " << arg2 << std::endl;
}

int main(int argc, char **argv)
{
	Callback<void (*)(int, const std::string &), int, const std::string &> clb1(fct1, 2);
	clb1.call("hello world !!!");

	return 0;
}

