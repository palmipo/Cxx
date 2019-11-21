#ifndef PIA_H
#define PIA_H

#include <cstdint>

class PIA
{
public:
	PIA() {}
	
	virtual void set(uint8_t port, uint8_t value) = 0;
	virtual uint8_t get(uint8_t port) = 0;
};

#endif
