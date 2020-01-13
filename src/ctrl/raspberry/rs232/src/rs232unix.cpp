#include "rs232.h"
#include "rs232exception.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <sys/ioctl.h>
#include <poll.h>
#include <unistd.h>
#include <cerrno>
#include <sstream>
// #include <iostream>
#include <iomanip>
#include "log.h"

RS232::RS232(const std::string & device_p)
: PollDevice()
{
	{
	std::stringstream ss;
    ss << "ouverture device : " << device_p;
    Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

    // ouverture du port
    _handler = ::open(device_p.c_str(), O_RDWR | O_NOCTTY);
    if (_handler < 0)
	{
		std::stringstream ss;
		ss << "open : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str());
	}

    if (!::isatty(_handler))
	{
		std::stringstream ss;
		ss << "isatty : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

    // lecture de la configuration actuelle
    if (::tcgetattr(_handler, &_oldios))
	{
		std::stringstream ss;
		ss << "tcgetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}
}

RS232::~RS232()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "close");

    ::tcflush(_handler, TCIOFLUSH);

    // fin connexion
    ::cfsetispeed (&_oldios, B0);
    ::cfsetospeed (&_oldios, B0);
    ::tcsetattr (_handler, TCSANOW, &_oldios);

    // fermeture du port
    if (!::close(_handler))
		Log::getLogger()->error(__FILE__, __LINE__, std::strerror(errno));
}

/*
baud   : B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400
data   : 8/7/6/5
parity : O/E/N
stop   : 1/2
*/
void RS232::setConfig(speed_t baud, int32_t data, int32_t parity, int32_t stop, int32_t is_raw)
{
	// std::stringstream ss;
    // ss << " baud : " << baud;
	// ss << ", data : " << data;
	// ss << ", parity : " << parity;
	// ss << ", stop : " << stop;
	// ss << ", is_raw : " << is_raw;
    // Log::getLogger()->DEBUG(__FILE__, __LINE__, ss.str());

    ::memset(&_newios, 0, sizeof(struct termios));

    if (::cfsetispeed (&_newios, baud) < 0)
	{
		std::stringstream ss;
		ss << "cfsetispeed : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

    if (::cfsetospeed (&_newios, baud) < 0)
	{
		std::stringstream ss;
		ss << "cfsetospeed : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

    if (parity == 'O') // impair
    {
		_newios.c_cflag |= _newios.c_cflag | PARENB | PARODD;
		_newios.c_iflag &= ~IGNPAR;
    }
    else if (parity == 'E') // pair
    {
		_newios.c_cflag |= (_newios.c_cflag & ~PARODD) | PARENB;
		_newios.c_iflag &= ~IGNPAR;
    }
    else
    {
		_newios.c_cflag &= ~(PARENB | PARODD);
		_newios.c_iflag |= IGNPAR;
    }
    
    if (data == 8)
    {
		_newios.c_cflag |= (_newios.c_cflag & ~CSIZE) | CS8;
    }
    else if (data == 7)
    {
		_newios.c_cflag |= (_newios.c_cflag & ~CSIZE) | CS7;
    }
    else if (data == 6)
    {
		_newios.c_cflag |= (_newios.c_cflag & ~CSIZE) | CS6;
    }
    else
    {
		_newios.c_cflag |= (_newios.c_cflag & ~CSIZE) | CS5;
    }
    
    if (stop == 2)
    {
		_newios.c_cflag |= CSTOPB;
    }
    else
    {
		_newios.c_cflag &= ~CSTOPB;
    }

    _newios.c_cflag |= CREAD | CLOCAL;
    _newios.c_iflag |= IGNBRK;
    _newios.c_oflag = 0;
    _newios.c_lflag = (is_raw == 0) ? 0 : ICANON;
    _newios.c_cc[VTIME] = 0;
    _newios.c_cc[VMIN]  = 0;

    if (::tcflush(_handler, TCIOFLUSH) < 0)
	{
		std::stringstream ss;
		ss << "tcflush : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, errno, this);
	}

    if (::tcsetattr (_handler, TCSANOW, &_newios) < 0)
	{
		std::stringstream ss;
		ss << "tcsetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}
}

int32_t RS232::write(uint8_t * cmd_p, int32_t cmd_length_p)
{
	std::stringstream ss;
	ss << "rs232 out (" << cmd_length_p << ") :" << std::hex;
	for (int32_t i=0; i<cmd_length_p; ++i)
	{
		ss << " " << std::setfill('0') << std::setw(2) << (int)cmd_p[i];
	}
	ss << std::dec << std::endl;
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	int32_t len = ::write(_handler, cmd_p, cmd_length_p);
	if (len < 0)
	{
		std::stringstream ss;
		ss << "write : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

	return len;
}

int32_t RS232::read(uint8_t * cmd_p, int32_t cmd_length_p)
{

	int32_t len = ::read(_handler, cmd_p, cmd_length_p);
	if (len < 0)
	{
		std::stringstream ss;
		ss << "read : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

	std::stringstream ss;
	ss << "rs232 in (" << len << ") :" << std::hex;
	for (int32_t i=0; i<len; ++i)
	{
		ss << " " << std::setfill('0') << std::setw(2) << (int)cmd_p[i];
	}
	ss << std::dec << std::endl;
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	return len;
}

int32_t RS232::recvUntilEnd(uint8_t * data, int32_t data_length)
{
	int32_t retry = 0, nb, cpt = 0;
	do
	{
		nb = RS232::read(data+cpt, data_length-cpt);
		cpt += nb;
		retry += 1;
	}
	while (nb && (retry < 5));
    
	return cpt;
}

void RS232::setInterCharacterTimer(int32_t timeout)
{
	if (::tcgetattr(_handler, &_newios))
	{
		std::stringstream ss;
		ss << "tcgetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

	_newios.c_cc[VTIME] = timeout & 0xFF;

	if (::tcsetattr (_handler, TCSANOW, &_newios) < 0)
	{
		std::stringstream ss;
		ss << "tcsetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}
}

int32_t RS232::getInterCharacterTimer()
{
	if (::tcgetattr(_handler, &_newios))
	{
		std::stringstream ss;
		ss << "tcgetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

	return _newios.c_cc[VTIME];
}

void RS232::setBlockingReadUntilCharacterArrives(int32_t nb)
{
	if (::tcgetattr(_handler, &_newios))
	{
		std::stringstream ss;
		ss << "tcgetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

	_newios.c_cc[VMIN] = nb & 0xFF;

	if (::tcsetattr (_handler, TCSANOW, &_newios) < 0)
	{
		std::stringstream ss;
		ss << "tcsetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}
}

int32_t RS232::getBlockingReadUntilCharacterArrives()
{
	if (::tcgetattr(_handler, &_newios))
	{
		std::stringstream ss;
		ss << "tcgetattr : " << strerror(errno);
		throw RS232Exception(__FILE__, __LINE__, ss.str(), this);
	}

	return _newios.c_cc[VMIN];
}

int32_t RS232::actionIn()
{
	return 0;
}

int32_t RS232::actionOut()
{
	return 0;
}

int32_t RS232::actionError()
{
	return 0;
}
