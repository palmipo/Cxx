#include "etherio.h"
#include "util.h"
#include <sstream>
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << argv[0] << "<ip>" << std::endl;
		return -1;
	}

	try
	{
		EtherIO manette(argv[1]);
		manette.init(0, 0, 0, 0, 0);
		manette.init(1, 0, 0, 0, 0);
		manette.init(2, 0, 0, 0, 0);
		manette.set(0, 0xFF);
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

