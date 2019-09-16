#include "ixxatfactory.h"
#include "sockettcp.h"
#include "ixxatcanatnet.h"
#include "polldevice.h"

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

Ixxat::Factory::Factory()
: PollFactory()
{}

Ixxat::Factory::~Factory()
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::Factory"));
	LOG4CXX_DEBUG(logger, "~Factory !");
}

Ixxat::CanAtNet * Ixxat::Factory::usbToCan(const std::string & addr)
{}

Ixxat::CanAtNet * Ixxat::Factory::canAtNet(const std::string & addr, int16_t port)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::Factory"));
	LOG4CXX_DEBUG(logger, "canAtNet !");

	Socket::SocketTcp * socket = new Socket::SocketTcp();
	socket->connexion(addr, port);
	
	Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(socket);
	add(ixxat);
	return ixxat;
}

int32_t Ixxat::Factory::actionError(PollDevice * device)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::Factory"));
	LOG4CXX_DEBUG(logger, "actionError !");

	return device->actionError();
}

int32_t Ixxat::Factory::actionIn(PollDevice * device)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::Factory"));
	LOG4CXX_DEBUG(logger, "actionIn !");

	return device->actionIn();
}

int32_t Ixxat::Factory::actionOut(PollDevice * device)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::Factory"));
	LOG4CXX_DEBUG(logger, "actionOut !");

	return device->actionOut();
}
