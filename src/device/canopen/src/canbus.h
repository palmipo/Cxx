#ifndef CANBUS_H
#define CANBUS_H

#include "polldevice.h"

class CanBus : public PollDevice
{
	public:
		CanBus();
		virtual ~CanBus();

		virtual int32_t write(uint8_t * msg, int32_t length);
		virtual int32_t read(uint8_t * msg, int32_t length);

		virtual void actionIn() = 0;
		virtual void actionOut() = 0;
		virtual void actionError() = 0;
};

#endif /* CANBUS_H */
