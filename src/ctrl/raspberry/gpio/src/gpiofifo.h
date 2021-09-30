#ifndef GPIO_FIFO_H
#define GPIO_FIFO_H

#include "gpiofactory.h"
#include <queue>

class GpioEvent;
class GpioFifo : public GpioFactory
{
	public :
		GpioFifo(const std::string &);
		virtual ~GpioFifo();
	
		// lecture des events et stockage
		virtual int32_t actionIn(PollDevice*);
		
	protected:
		std::queue < GpioEvent * > _fifo;
};

#endif /* GPIO_FIFO_H */
