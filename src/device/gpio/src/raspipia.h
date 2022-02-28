#ifndef RASPIPIA_H
#define RASPIPIA_H

#include "PIA.h"

class RaspiGpio;
class RaspiPia : public PIA
{
public:
	RaspiPia(RaspiGpio *);
	virtual ~RaspiPia();

	virtual void write(uint8_t);
	virtual int8_t read();
};

#endif /* RASPIPIA_H */

