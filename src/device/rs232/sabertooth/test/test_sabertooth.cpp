#include "rs232.h"
#include "sabertooth.h"
#include "moteurcc.h"
#include "joystick.h"
// #include "util.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>

void reception(void *user_data)
{
	RS232 *uart = (RS232 *)user_data;

	s8 *cmd = new s8[100];
	s32 len = uart->get(cmd, 100);
	std::cout << "reception : " << len << "caracteres." << std::endl;
	for (int i=0; i<len; ++i)
		std::cout << (int)cmd[i] << " " << std::endl;
	delete[] cmd;
}

void bouton(unsigned char id, short value, void * param)
{
	std::cout << "bouton[" << (int)id << "] = " << value << std::endl;

	Sabertooth * ctrl = (Sabertooth *)param;
	ctrl->getMoteur(0)->setDirection(value);
	ctrl->getMoteur(1)->setDirection(value);
	ctrl->action();
}

void axe(unsigned char id, short value, void * param)
{
	std::cout << "axe[" << (int)id << "] = " << value << std::endl;

	Sabertooth * ctrl = (Sabertooth *)param;
	ctrl->getMoteur(0)->setDirection(value);
	ctrl->getMoteur(1)->setDirection(value);
	ctrl->action();
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		std::cout << argv[0] << " </dev/ttyS0> </dev/input/jsX> </dev/input/eventXX>" << std::endl;
		return -1;
	}

	try
	{
		RS232 uart(argv[1]);
		uart.setConfig(9600, 8, 'N', 1, 1);
	
		Sabertooth ctrl(&uart);

		Joystick manette(argv[1], argv[2]);
		manette.setButtonCallback(bouton, &ctrl);
		manette.setAxisCallback(axe, &ctrl);
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
