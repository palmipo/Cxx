#include "pollexception.h"
#include "log.h"
#include "antfactory.h"
#include "anthr.h"
#include "antctrl.h"
#include "anttempe.h"
#include "antspeedcadence.h"
#include <cstdint>
#include <thread>
#include <iostream>
#include <sstream>


void * thread_poll_start(ANT::AntFactory * factory, int32_t * fin)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "DEBUT thread");

	while(! *fin)
	{
		try
		{
			factory->scrute(1000);
		}
		// catch(ANT::AntException e)
		// {
			// std::stringstream ss;
			// ss << "thread exception " << e.what();
			// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		// }
		catch(PollException e)
		{
			std::stringstream ss;
			ss << "thread exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(...)
		{
			Log::getLogger()->debug(__FILE__, __LINE__, "thread exception");
		}
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "FIN thread");
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << argv[0] << " </dev/ttyUSB0>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}

	int32_t tempo = 60; // 1min

	int32_t fin = 0;
	ANT::AntFactory factory(argv[1]);
	std::thread t1(thread_poll_start, &factory, &fin);

	try
	{
		
		ANT::SpeedCadence * sc = factory.addSpeedCadenceMonitor();
		sc->init();
		std::this_thread::sleep_for(std::chrono::seconds(tempo));

		ANT::HeartRate * hr = factory.addHRMonitor();
		hr->init();
		std::this_thread::sleep_for(std::chrono::seconds(tempo));

		ANT::Tempe * tempe = factory.addTempeMonitor();
		tempe->init();
		std::this_thread::sleep_for(std::chrono::seconds(tempo));

		//~ std::cout << "init ctrl sensor" << std::endl;
		//~ ANT::Ctrl * ctrl = factory.addVideoCtrlMaster();
		//~ ctrl->init();

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

	fin = 1;
	t1.join();

	return 0;
}
