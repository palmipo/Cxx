#ifndef HC_SR04_H
#define HC_SR04_H

#include "gpiofactory.h"

class HC_SR04 : public GpioFactory
{
	public:
		HC_SR04(const std::string & gpio_dev, int32_t OUT_PIN, int32_t IRQ_PIN);
		int64_t distance();

	protected:
		virtual int32_t actionIn(PollDevice * device);
		virtual int32_t actionOut(PollDevice * device);
		virtual int32_t actionError(PollDevice * device);
		
		// nanosecond
		int64_t timestamp_rising;
		int64_t timestamp_falling;

};

#endif /* HC_SR04_H */
