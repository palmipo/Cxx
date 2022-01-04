#ifndef SK9822_IO_H
#define SK9822_IO_H

#include <cstdint>

class SK9822_io
{
	public:
		SK9822_io()
		{}
		
		virtual ~SK9822_io()
		{}
	
		virtual void write_bit(uint8_t bit) = 0;
};

#endif
