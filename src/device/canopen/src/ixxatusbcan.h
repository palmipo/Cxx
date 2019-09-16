#ifndef CANBUS_H
#define CANBUS_H

#include "polldevice.h"

class CanBus : public PollDevice
{
	public:
		CanBus();
		virtual ~CanBus();

		virtual void connexion(const std::string &);
		virtual int32_t write(uint8_t * msg, int32_t length);
		virtual int32_t read(uint8_t * msg, int32_t length);

		virtual void actionIn();
		virtual void actionOut();
		virtual void actionError();
};

#endif /* CANBUS_H */
