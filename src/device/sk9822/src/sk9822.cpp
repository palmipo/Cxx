#include "sk9822.h"
#include "sk9822_io.h"

SK9822::SK9822(SK9822_io * io)
: _io(io)
{}

SK9822::~SK9822()
{}

void SK9822::write(uint32_t *rgb, uint32_t length)
{
	int32_t len = length & 0x1F;

	start_frame();
	for (int32_t i=0; i<len; ++i)
	{
		data_frame(i, (rgb[i] & 0xFF0000) >> 16, (rgb[i] & 0xFF00) >> 8, rgb[i]&0xFF);
	}
	stop_frame();
}

void SK9822::start_frame()
{
	for (int32_t i=0; i<32; ++i)
	{
		_io->write_bit(0);
	}
}

void SK9822::data_frame(uint8_t num, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t data[4];
	data[3] = r;
	data[2] = g;
	data[1] = b;
	data[0] = 0xE0 | (num & 0x1F);
	for (int32_t i=0; i<4; ++i)
	{
		for (int32_t j=0; j<8; ++j)
		{
			_io->write_bit((data[i] & (7-j)) ? 1:0);
		}
	}
}

void SK9822::stop_frame()
{
	for (int32_t i=0; i<32; ++i)
	{
		_io->write_bit(1);
	}
}
