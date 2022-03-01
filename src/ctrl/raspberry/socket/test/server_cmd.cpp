#include "socketfactory.h"
#include "socketexception.h"
#include "sockettcp.h"
#include <iostream>

static int32_t actionIn(PollDevice* dev, void *)
{
	Socket::SocketTcp * server = (Socket::SocketTcp *)dev;

	try
	{
		u8 msg[256];
		s32 len = server->read(msg, 256);

		u8 rcv[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x04, 0x06, 0x00, 0x02, 0x00, 0xFF};
		server->write(rcv, 12);
	}
	catch (Socket::SocketException & e)
	{
	}

	return 0;
}

int main (int argc, char **argv)
{
 	try
	{
		Socket::SocketFactory socket_factory;
		Socket::SocketTcp * socket = socket_factory.addTcpServer("0.0.0.0", 502);

PollFactory poll_factory;
		poll_factory.setActionInCallback(actionIn);
poll_factory.add(socket);

		while(1)
		{
			poll_factory.scrute(60000);
		}
	}
	catch (Socket::SocketException & e)
	{
	}

	return 0;
}
