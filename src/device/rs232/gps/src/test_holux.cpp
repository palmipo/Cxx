#include "rs232.h"
#include "rs232exception.h"
#include <iostream>
#include <cstring>

void trame_gps(void * user_data)
{
	std::cout << "trame gps" << std::endl;
}

int main(int argc, char **argv)
{
	try
	{
		RS232 serial(argv[1]);
		serial.setCallback(trame_gps, &serial);

		u8 msg[100];
		msg[0] = 'R';
		msg[1] = 'D';
		msg[2] = 0xD;
		msg[3] = 0xA;
		serial.set((s8*)msg, (s32)4);
		
		while(1)
		{
			serial.scrute(1000);
		}
	}
	catch(...)
	{
		std::cout << "erreur" << std::endl;
		return -1;
	}

	return 0;
}

