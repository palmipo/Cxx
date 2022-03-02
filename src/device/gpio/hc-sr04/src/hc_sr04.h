#ifndef HC_SR04_H
#define HC_SR04_H

#include <cstdint>

class PIA;
class HC_SR04
{
	public:
		HC_SR04(PIA *);
		virtual ~HC_SR04();

		virtual void start();
		
		virtual void setTimeRising(uint64_t);
		virtual void setTimeFalling(uint64_t);

		virtual int32_t isBusy();
		virtual uint64_t distance();

	protected:
		PIA * _out;
		int32_t _status;
		uint64_t _distance;
		uint64_t _timestamp_rising;
		uint64_t _timestamp_falling;
};

#endif /* HC_SR04_H */
