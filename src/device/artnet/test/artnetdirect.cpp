#include "socketudp.h"
#include <cstring>
#include <cstdint>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		return -1;
	}

	try
	{
		Socket::SocketUdp sock;
		sock.broadcast(0x1936);
		
		uint8_t data[530];
		memset(data, 0, 530);
		
		// entete
		data[0] = 'A';
		data[1] = 'r';
		data[2] = 't';
		data[3] = '-';
		data[4] = 'N';
		data[5] = 'e';
		data[6] = 't';
		data[7] = 0;
		data[8] = 0;
		data[9] = 0x50;
		data[10] = 0;
		data[11] = 0x0E;
		data[12] = 1;
		data[13] = 0;
		data[14] = 0;
		data[15] = 0;
		data[16] = 0x02;
		data[17] = 0x00;
		
		// data
		data[18] = std::strtol(argv[1], 0, 0);
		data[19] = std::strtol(argv[2], 0, 0);
		data[20] = std::strtol(argv[3], 0, 0);
		sock.write(data, 530);
		return 0;
	}
	catch(...)
	{
		return -1;
	}
}

