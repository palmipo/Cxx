#include "ixxatcanatnet.h"
#include "canopenfactory.h"
#include "canopen.h"
#include "canopensdo.h"
#include "log.h"
#include <thread>
#include <mutex>
#include <poll.h>
#include <sstream>

void scrute(CAN::CANOpenFactory * ixxat, int32_t * fin)
{
	while (! *fin)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "scrute");
		ixxat->scrute(1000);
	}
	Log::getLogger()->debug(__FILE__, __LINE__, "fin thread secondaire");
}

int main(int argc, char ** argv)
{
	int32_t fin = 0;
	CAN::CANOpenFactory factory;
	std::thread t(scrute, &factory, &fin);
	try
	{
		CAN::CANOpen * canopen = factory.canAtNet(5, "192.168.1.207");
		std::this_thread::sleep_for(std::chrono::seconds(60));

		canopen->sdo()->writeDictionary(0x1018, 0x03, 0, 0);
		std::this_thread::sleep_for(std::chrono::seconds(10));
		
		int32_t len = 0;
		uint16_t index = 0;
		uint8_t subindex = 0;
		uint8_t msg[4];
		
		std::stringstream ss;
		len = canopen->sdo()->readDictionary(index, subindex, msg, 4);
		ss << "read : " << len << " " << std::hex << " " << (int)index << " " << (int)subindex;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	catch(...)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "exception !!!");
	}
	fin = 1;
	t.join();

	return 0;
}
