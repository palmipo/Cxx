#include "etherio.h"
#include "socketudp.h"
#include "socketexception.h"
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	try{
		Socket::SocketUdp socket("0.0.0.0", 2424);
		socket.connexion(argv[1], 2424);
		EtherIO pia(&socket);
		pia.identifyUnit();

		std::cout << (int)pia.getDirection(0) << std::endl;
		std::cout << (int)pia.getDirection(1) << std::endl;
		std::cout << (int)pia.getDirection(2) << std::endl;
		// pia.setAutoScan(2, 2, 2);

		pia.set(0, 0);
		pia.set(1, 0xFF);

		std::cout << "lecteur eeprom : " << std::hex << std::endl;
		for (u8 i=5; i<25; i+=1)
			std::cout << (int)i << " " << pia.readEEPROM(i) << std::endl;
		std::cout << std::dec << std::endl;
		// u16 mask = 1;
		
		// std::cout << std::hex;
		while (1)
		{

			// pia.set(0, mask);
			// mask <<= 1;
			// if (mask > 255) mask = 1;

			//~ if (fact.scrute(1000) > 0)
			{
				// u8 input = pia.get(2);
				//~ pia.set(0, input);
				// std::cout << " 0x" << (int)input;
			}
		}
		// std::cout << std::dec << std::endl;
		// pia.resetModule();
	}
	catch(Socket::SocketException e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch(...)
	{
		return -1;
	}

	return 0;
}
	
