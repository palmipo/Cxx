#ifndef GPIO_EVENT_H
#define GPIO_EVENT_H

#include <cstdint>

class GpioEvent
{
	public:
		GpioEvent(uint32_t, uint64_t);
	
		uint64_t timestamp();
		uint32_t id();
	
	protected:
		uint64_t _timestamp;
		uint32_t _id;
};

#endif /* GPIO_EVENT_H */
