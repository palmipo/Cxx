//~ #include "rs232factory.h"
//~ #include "rs232.h"
#include "antfactory.h"
#include "anthr.h"
#include "antctrl.h"
#include "anttempe.h"
#include "antspeedcadence.h"
#include <cstdint>

#include <iostream>

int main(int argc, char **argv)
{
	int32_t tempo = 100; // 1min
	
	try
	{
		ANT::AntFactory factory("/dev/ttyUSB0");
		
		ANT::SpeedCadence * sc = factory.addSpeedCadenceMonitor();
		sc->init();

		ANT::HeartRate * hr = factory.addHRMonitor();
		hr->init();

		ANT::Tempe * tempe = factory.addTempeMonitor();
		tempe->init();

		//~ std::cout << "init ctrl sensor" << std::endl;
		//~ ANT::Ctrl * ctrl = factory.addVideoCtrlMaster();
		//~ ctrl->init();

		int32_t cpt = 0;
		while (cpt < 1000)
		{
			factory.scrute(100);
			cpt += 1;
		}

		// tempe->sendDataPageRequest(0x52);
		// tempe->sendTimeDate(16, 0, 0, 18, 9, 4);
		// hr->setSportMode(ANT::HeartRate::Swimming);
	
		//~ factory.close(hr->channelNumber());
		//~ factory.close(tempe->channelNumber());
	}
	catch(...)
	{
		return -1;
	}

	return 0;
}
