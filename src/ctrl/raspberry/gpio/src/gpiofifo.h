#ifndef GPIO_FIFO_H
#define GPIO_FIFO_H

#include "gpio.h"
#include <queue>

class GpioFifo : public Gpio
{
	public :
		GpioFifo(int32_t, int32_t);
		virtual ~GpioFifo();

		virtual int32_t getEvent(uint32_t *, uint64_t *);
		virtual int32_t actionIn();
		
	protected:
		std::queue < GpioEvent > _fifo;
};

#endif /* GPIO_FIFO_H */
