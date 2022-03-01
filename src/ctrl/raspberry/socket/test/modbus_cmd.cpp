#include "socketfactory.h"
#include "sockettcp.h"
#include "socketexception.h"
#include "log.h"
#include <sstream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << argv[0] << " <ip>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}

	try
	{
		Socket::SocketFactory factory;
		Socket::SocketTcp * sock = (Socket::SocketTcp *)factory.addTcpConnection(argv[1], 502);
		if (sock)
		{
			uint8_t msg[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0xF8, 0x10, 0x00, 0x01, 0x02, 0x00, 0xFF};
			sock->write(msg, 13);

			uint8_t rep[100];
			sock->read(rep, 100);
		}
	}
	catch(Socket::SocketException e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}
	catch(...)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "exception.");
	}

	return 0;
}
