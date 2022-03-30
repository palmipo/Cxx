#ifndef RASPIUART_H
#define RASPIUART_H

#include "ctrluart.h"
#include <cstdint>

class RS232;
class RaspiUart : public CtrlUART
{
public:
	RaspiUart(RS232 *);
	virtual ~RaspiUart();

	virtual int32_t read(uint8_t *, int32_t);
	virtual int32_t write(uint8_t *, int32_t);

protected:
	RS232 * _serial;
};

#endif /* RASPIUART_H */
