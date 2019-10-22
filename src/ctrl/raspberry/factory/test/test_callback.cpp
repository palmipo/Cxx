#include "callback.h"
#include <iostream>
#include <string>

void fct(int arg1, const std::string & arg2)
{
	std::cout << "fct " << arg1 << " " << arg2 << std::endl;
}

int main(int argc, char **argv)
{
	Callback<void (*)(int, const std::string &), int, const std::string &> clb(fct, 2);
	clb.call("hello world !!!");

	return 0;
}

