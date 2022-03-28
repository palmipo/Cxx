#ifndef RASPIPIA_H
#define RASPIPIA_H

#include "ctrlpia.h"

class RaspiGpio;
class RaspiPia : public CtrlPia
{
	public:
		RaspiPia(RaspiGpio *);
		virtual ~RaspiPia();

		virtual void write(uint8_t);
		virtual uint8_t read();
	
	protected:
		RaspiGpio * _gpio;
};

#endif /* RASPIPIA_H */
