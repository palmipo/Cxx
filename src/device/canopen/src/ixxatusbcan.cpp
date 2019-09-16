#include "canopen.h"
// #include "pollexception.h"

#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

/* constructeur socket client */
CanBus::CanBus()
: PollDevice()
{}


CanBus::~CanBus()
{
    ::close(_handler);
}


void CanBus::connexion(const std::string & cnx)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("CanBus"));

	struct ifreq ifr;
	struct sockaddr_can addr;
	::memset(&ifr, 0x0, sizeof(ifr));
	::memset(&addr, 0x0, sizeof(addr));
	
	/* open CAN_RAW socket */
	_handler = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
	
	/* convert interface sting "can0" into interface index */
	::strcpy(ifr.ifr_name, cnx.c_str());
	
	::ioctl(_handler, SIOCGIFINDEX, &ifr);
	
	/* setup address for bind */
	addr.can_ifindex = ifr.ifr_ifindex;
	addr.can_family = PF_CAN;
	
	/* bind socket to the can0 interface */
	::bind(_handler, (struct sockaddr *)&addr, sizeof(addr));
}


int32_t CanBus::write(uint8_t * msg, int32_t length)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("CanBus"));

	struct can_frame frame;
	::memset(&frame, 0x0, sizeof(frame));

	/* first fill, then send the CAN frame */
	frame.can_id = 0x23;
	::memcpy((char *)frame.data, msg, length);
	frame.can_dlc = length;

	int32_t len = ::write(_handler, &frame, sizeof(frame));

    return len;
}

int32_t CanBus::read(uint8_t * msg, int32_t length)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("CanBus"));

	struct can_frame frame;
	::memset(&frame, 0x0, sizeof(frame));

	int32_t len = ::read(_handler, &frame, sizeof(frame));
	::memcpy(msg, (char *)frame.data, length);
    return len;
}

void CanBus::actionError()
{}

void CanBus::actionIn()
{}

void CanBus::actionOut()
{}

