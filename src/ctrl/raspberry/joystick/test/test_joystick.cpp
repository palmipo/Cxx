#include "joystick.h"
#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>

void bouton(unsigned char id, short value, void * param)
{
	std::cout << "bouton[" << (int)id << "] = " << value << std::endl;
}

void axe(unsigned char id, short value, void * param)
{
	std::cout << "axe[" << (int)id << "] = " << value << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << argv[0] << "</dev/input/jsX> </dev/input/eventXX>" << std::endl;
		return -1;
	}

	try
	{
		Joystick manette(argv[1], argv[2]);
		manette.setButtonCallback(bouton, 0);
		manette.setAxisCallback(axe, 0);
		manette.buttonCount();
		manette.axisCount();

		while (1)
		{
			manette.scrute(30000);
		}
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

