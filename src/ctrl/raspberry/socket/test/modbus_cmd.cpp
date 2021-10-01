#include "socketfactory.h"
#include "sockettcp.h"
#include "socketexception.h"
#include "log.h"
#include <sstream>

class Factory : public Socket::SocketFactory
{
	public:
		Factory()
		{}

		virtual int32_t actionIn(PollDevice * device)
		{}

		virtual int32_t actionOut(PollDevice * device)
		{}

		virtual int32_t actionError(PollDevice * device)
		{}
};

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
		Factory factory;
		Socket::SocketTcp * sock = (Socket::SocketTcp *)factory.addTcpConnection(argv[1], 502);
		if (sock)
		{
			uint8_t msg[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0xF8, 0x10, 0x00, 0x01, 0x02, 0x00, 0xFF};

			int32_t len = sock->write(msg, 13);
			factory.scrute(10000);
			uint8_t rep[100];
			len = sock->read(rep, 100);
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
