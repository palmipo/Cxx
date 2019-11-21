#include "rs232.h"
#include "lunartec.h"
#include <iostream>

class LunartecServer
{
	public:
		LunartecServer()
		{
			SocketTcp * sock_srv = sock_fact.addTcpServer("0.0.0.0", 2222);
			sock_serv.setCallback(new_connexion, this);

			RS232 * uart = serial_fact.addSerialConnection("/dev/ttyUSB0");

			lunartec = new Lunartec(1, &uart);
		}
		
		virtual ~LunartecServer()
		{
			delete lunartec;
		}

	protected:
			SocketFactory sock_fact;
			SocketTcp * sock_srv;

			RS232Factory serial_fact;
			RS232 * uart;

			Lunartec * lunartec;

	protected:
		static void new_data(void * data)
		{
			SocketTcp * sock = (SocketTcp *)data;

			u8 msg[100];
			s32 len = sock->read(msg, 100);
			lunartec->send(msg, len);
		}

		static void new_connexion(s32 handle, void * data)
		{
			SocketFactory * sock_fact = (SocketFactory *)data;
			SocketTcp * sock = sock_fact->getTcp(handle);
			sock->setCallback(new_data, this);
		}
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " /dev/ttyUSB0" << std::endl;
		return -1;
	}
	
	try
	{
		LunartecServer srv;
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

