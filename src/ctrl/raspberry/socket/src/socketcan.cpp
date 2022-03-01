#include "socketcan.h"
#include "socketexception.h"
#include <sys/ioctl.h>
#include <net/if.h>
#if defined __MINGW64__ || defined __MINGW32__ || defined __CYGWIN__
#else
	#include <linux/sockios.h>
	#include <linux/can.h>
	#include <linux/can/raw.h>
#endif
// #include <thread>
#include <cerrno>
#include <cstring>
#include <unistd.h>

/* constructeur socket client */
Socket::SocketCan::SocketCan()
: PollDevice()
{}


Socket::SocketCan::~SocketCan()
{
	::close(_handler);
}


void Socket::SocketCan::connexion(const std::string & interface)
{
#if defined __MINGW64__ || defined __MINGW32__ || defined __CYGWIN__
#else
	struct ifreq ifr;
	struct sockaddr_can addr;
	::memset(&ifr, 0x0, sizeof(ifr));
	::memset(&addr, 0x0, sizeof(addr));
	
	/* open CAN_RAW socket */
	_handler = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (_handler < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}
	
	/* convert interface sting "can0" into interface index */
	::strcpy(ifr.ifr_name, interface.c_str());
	if (::ioctl(_handler, SIOCGIFINDEX, &ifr) < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}
	
	/* setup address for bind */
	addr.can_ifindex = ifr.ifr_ifindex;
	addr.can_family = AF_CAN;
	
	/* bind socket to the can0 interface */
	if (::bind(_handler, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}
#endif
}


int32_t Socket::SocketCan::write(uint8_t * data, int32_t length)
{
	int32_t len = ::write(_handler, data, length);
	if (len < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}

	return len;
}

int32_t Socket::SocketCan::read(uint8_t * data, int32_t length)
{
	int32_t len = ::read(_handler, data, length);
	if (len < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}

	return len;
}

