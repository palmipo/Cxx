#include "joystick.h"
#include "forcefeedback.h"
#include "pollfactory.h"
#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>

static int32_t actionIn(PollDevice * device)
{
	uint8_t data[4];
	int32_t len = device->read(data, 4);
	
	return len;
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << argv[0] << " </dev/input/jsX> </dev/input/eventX>" << std::endl;
		return -1;
	}

	try
	{
		Joystick manette(argv[1]);
		manette.buttonCount();
		manette.axisCount();
		
		ForceFeedback ff(argv[2]);

		PollFactory factory;
		factory.setActionInCallback(actionIn);
		factory.add(&manette);
		factory.add(&ff);

		while (1)
		{
			factory.scrute(30000);
		}
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

