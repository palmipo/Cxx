#include "spi.h"
#include "spiexception.h"
#include <iostream>
#include <cstring>

s32 ajout_octet(u8 * buffer, s32 nbit, u8 octet)
{
	// start = 0
	s32 num_octet = nbit >> 3;
	s32 num_bit = 7 - (nbit % 8);
	std::cout << nbit << " " << num_octet << " " << num_bit << " " << (int)buffer[num_octet] << std::endl;
	nbit+=1;

	// octet
	for (s32 i=0; i<8; i+=1)
	{
		num_octet = nbit >> 3;
		num_bit = 7 - (nbit % 8);
		buffer[num_octet] |= ((octet >> i) & 0x01) << num_bit;
		std::cout << nbit << " " << num_octet << " " << num_bit << " " << (int)buffer[num_octet] << std::endl;
		nbit += 1;
	}

	// stop = 1
	num_octet = nbit >> 3;
	num_bit = 7 - (nbit % 8);
	buffer[num_octet] |= 1 << num_bit;
	std::cout << nbit << " " << num_octet << " " << num_bit << " " << (int)buffer[num_octet] << std::endl;
	nbit+=1;

	num_octet = nbit >> 3;
	num_bit = 7 - (nbit % 8);
	buffer[num_octet] |= 1 << num_bit;
	std::cout << nbit << " " << num_octet << " " << num_bit << " " << (int)buffer[num_octet] << std::endl;
	nbit+=1;
	
	return nbit;
}

int main(int argc, char ** argv)
{
	try
	{
		SPI spi(argv[1]);

		// CPOL = 0x02
		// SPI_LSB_FIRST = 0x08
		// SPI_NO_CS = 0x40
		spi.setMode(0x42);
		spi.setClockRate(25000);
		spi.setBitPerWord(8);

		//  8 bits a 1
		// 22 bits a 0
		//  2 bits a 1
		// a faire 96 fois :
		//   1 bit a 0
		//   octet
		//   2 bits a 1
		// = 132+32
		u8 octet[96];
		memset(octet, 0x0F, 96);

		u8 buffer[512];
		u8 rcv[512];
		memset(buffer, 0, 512);
		buffer[0] = 0xFF;
		buffer[1] = 0x00;
		buffer[2] = 0x00;
		buffer[3] = 0x03;
		s32 nbit = 32;
		for (s32 i=0; i<96; i+=1)
		{
			nbit = ajout_octet(buffer, nbit, octet[i]);
		}
		spi.transfert(buffer, rcv, 164);
	}
	catch(SPIException & e)
	{
		std::cout << "exception  " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "exception ..." << std::endl;
	}
	return 0;
}
