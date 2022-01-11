#include "etherio.h"
#include "socketudp.h"
#include "socketexception.h"
#include "pollfactory.h"
#include <iostream>
#include <iomanip>


static int32_t action(PollDevice * s)
{
	std::cout << "action !!!" << std::endl;
	Socket::SocketUdp * socket = (Socket::SocketUdp*) s;
	uint8_t data[1024];
	int32_t length = 1024;
	int32_t l = socket->read(data, length);
	std::cout << "reception de " << l << " caracteres : " << std::hex << data << std::dec << std::endl;
	return l;
}

static void clb_io24(uint8_t* mac, uint8_t* firmware)
{
	std::cout << "IO24 " << std::hex;
	for (int i=0; i<6; i++)
		std::cout << (int)mac[i] << ":";
	std::cout << std::dec << std::endl;
}

static void clb_host_data(uint32_t serial, uint8_t* sender_ip, uint8_t* sender_mac, uint16_t sender_port)
{
	std::cout << "IO24 " << serial << std::endl;
	for (int i=0; i<4; i++)
		std::cout << (int)sender_ip[i] << ".";
	std::cout << std::endl << std::hex;
	for (int i=0; i<6; i++)
		std::cout << (int)sender_mac[i] << ":";
	std::cout << std::endl;
	std::cout << std::dec << sender_port << std::endl;
}

static void get(uint8_t port, uint8_t valeur)
{
	std::cout << "get(" << (int)port << ")=0x" << std::hex << (int)valeur << std::dec << std::endl;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " ip" << std::endl;
		return -1;
	}

	try{
		//~ Socket::SocketUdp socket;
		//~ socket.connexion("0.0.0.0", 2424);
		//~ socket.broadcast(2424);
		//~ EtherIO pia(&socket);
		//~ pia.sendHostData();
		
		//~ Socket::SocketUdp socket("0.0.0.0", 2424);
		Socket::SocketUdp socket;
		//~ Socket::SocketUdp socket("192.168.10.90", 2424);
		socket.setReuseAddr(1);
		//~ socket.setBroadcast(1);
		socket.connexion("192.168.10.90", 2424);
		//~ socket.connexion("0.0.0.0", 2424);
		socket.broadcast(2424);

		EtherIO pia(&socket);

		pia.resetModule();

		//~ pia.identifyUnit(clb_io24);
		//~ pia.sendHostData(clb_host_data);
		
		//~ uint8_t addr[] = {192, 168, 10, 90};
		//~ pia.setIpFixe(addr);

		uint8_t Preset[] = {0, 0xff, 0xff};
		uint8_t Direction[] = {0xff, 0, 0};
		uint8_t Pull_Up[] = {0xff, 0, 0};
		uint8_t Threshold[] = {0xff, 0, 0};
		uint8_t SchmittTrigger[] = {0xff, 0, 0};
		pia.setPresetPort(Preset, Direction, Pull_Up, Threshold, SchmittTrigger);

		//~ uint8_t maskPortA=0xff;
		//~ uint8_t maskPortB=0;
		//~ uint8_t maskPortC=0;
		//~ uint8_t filterCount = 0;
		//~ uint16_t autoScanRate = 1;//50;
		//~ uint8_t mac_addr[] = {0xb8,0x27,0xeb,0x99,0x23,0xbf};
		//~ uint8_t ip_addr[] = {192,168,10,107};
		//~ uint16_t port_addr = 2424;
		//~ pia.setAutoScan(maskPortA, maskPortB, maskPortC, filterCount, autoScanRate, mac_addr, ip_addr, port_addr);


		// portA
		pia.setDirection(0, 0xff);
		pia.setPullup(0, 0xff);
		std::cout << "lecture de portA : 0x" << std::hex << (int)pia.get(0) << std::dec << std::endl;

		// portB
		pia.setDirection(1, 0);
		pia.set(1, 0);
		
		// portC
		pia.setDirection(2, 0);
		pia.set(2, 0);

		PollFactory factory;
		factory.add(&socket);
		factory.setActionInCallback(action);
		while (1)
		{
		std::cout << "lecture de portA : 0x" << std::hex << (int)pia.get(0) << std::dec << std::endl;
			factory.scrute(100);
		}
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
	
