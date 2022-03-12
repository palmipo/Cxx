#ifndef PIA_H
#define PIA_H

#include <cstdint>

class PIA
{
	public :
		PIA() 
		{}

		virtual ~PIA()
		{}

		virtual void write(uint8_t) = 0;
		virtual uint8_t read() = 0;

		//virtual void toggle() = 0;
		//virtual void sortieTemporiser(uint64_t) = 0;
};

#endif /* GPIO_H */
