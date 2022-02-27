#ifndef PIA_H
#define PIA_H

#include <cstdint>

class Pia
{
	public :
		Pia();
		virtual ~Pia();

		virtual void write(uint8_t) = 0;
		virtual int8_t read() = 0;
};

#endif /* GPIO_H */
