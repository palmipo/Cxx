#include "ixxatcanatnet.h"
#include "ixxatfactory.h"
#include "canopen.h"
#include <thread>
#include <mutex>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <poll.h>
bool fin = false;

void scrute(Ixxat::Factory * ixxat)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("ixxat"));

	while (!fin)
	{
		ixxat->scrute(1000);
		LOG4CXX_DEBUG(logger, "scrute !!!");
	}
}

int main(int argc, char ** argv)
{
 	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("main"));

	fin = false;
	try
	{
		Ixxat::Factory factory;

		std::thread t(scrute, &factory);
		t.detach();

		Ixxat::CanAtNet * bus = factory.canAtNet("192.168.1.207", 19227);
		// factory.scrute(1000);
		// factory.scrute(1000);

		CAN::CANOpen canopen(bus);
		std::this_thread::sleep_for(std::chrono::seconds(1));

		LOG4CXX_DEBUG(logger, "DEBUT TEMPO !!!");
		canopen.write(0xC, 0x5, 0x1018, 0x03, 0, 0);
		std::this_thread::sleep_for(std::chrono::seconds(10));
		LOG4CXX_DEBUG(logger, "FIN TEMPO !!!");
		// factory.scrute(1000);
		// factory.scrute(1000);
		// factory.scrute(1000);
		
		int32_t len = 0;
		uint8_t pdo;
		uint8_t node_id;
		uint16_t index;
		uint8_t subindex;
		uint8_t msg[4];
		// do
		// {
			len = canopen.read(&pdo, &node_id, &index, &subindex, msg, 4);
			LOG4CXX_DEBUG(logger, "read : " << len << " " << std::hex << (int)pdo << " " << (int)node_id << " " << (int)index << " " << (int)subindex);
			len = canopen.read(&pdo, &node_id, &index, &subindex, msg, 4);
			LOG4CXX_DEBUG(logger, "read : " << len << " " << (int)pdo << " " << (int)node_id << " " << (int)index << " " << (int)subindex);
		// } while (len);
		fin = true;
	}
	catch(...)
	{
		LOG4CXX_ERROR(logger, "exception !!!");
	}

	return 0;
}