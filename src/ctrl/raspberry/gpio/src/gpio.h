#ifndef GPIO_H
#define GPIO_H

#include "polldevice.h"
//~ #include "gpioevent.h"
// #include <termios.h>
// #include <string>
#include <queue>

class GpioEvent;
class Gpio : public PollDevice
{
	public :
		Gpio(int32_t, int32_t);
		virtual ~Gpio();

		virtual int32_t pinNumber() const;

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);
		virtual GpioEvent * getEvent();

		virtual int32_t actionIn();
		virtual int32_t actionOut();
		virtual int32_t actionError();
		
	protected:
		int32_t _pin_number;
		GpioEvent * _evnt;
};

#endif /* GPIO_H */
