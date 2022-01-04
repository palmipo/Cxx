#ifndef SK9822_GPIO_H
#define SK9822_GPIO_H

#include "sk9822_io.h"
#include <string>

class SK9822_gpio : public SK9822_io
{
	public:
		SK9822_gpio(const std::string &, int32_t, int32_t);
		virtual ~SK9822_gpio();
	
		virtual void write_bit(uint8_t bit);
		
	protected:
		int32_t _handler;
};

#endif
