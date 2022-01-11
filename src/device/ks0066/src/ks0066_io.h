#ifndef KS0066_IO_H
#define KS0066_IO_H

#include <cstdint>

class KS0066_io
{
	public:
		KS0066_io() {}
		virtual ~KS0066_io() {}

		virtual void set_register_select(uint8_t) = 0;
		virtual void set_read_write_(uint8_t) = 0;
		virtual void set_enable(uint8_t) = 0;
		virtual uint8_t get_data() = 0;
		virtual void set_data(uint8_t) = 0;
};

#endif
