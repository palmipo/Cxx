#include "codec.h"
#include <cstdint>
#include <iostream>

int main(int argc, char **argv)
{
	uint8_t src[] { 0x11, 0x22, 0x44, 0x88 };
	uint8_t * dst = new uint8_t [10];
	
	Codec codec;
	codec.encoder_decoder(dst, 0, src, 2, 30, 0);

	for (int i=0; i<4; ++i)
	{
		std::cout << std::hex << "0x" << (int32_t)dst[i] << std::endl;
	}

	delete[] dst;
	
	return 0;
}
