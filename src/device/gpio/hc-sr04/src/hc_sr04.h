#ifndef HC_SR04_H
#define HC_SR04_H

#include "gpiofactory.h"
#include <thread>

class Gpio;
class HC_SR04 : public GpioFactory
{
	public:
		HC_SR04(int32_t, int32_t);
		virtual ~HC_SR04();

		virtual void start(int32_t);
		virtual void stop();
		virtual int32_t status();
		virtual double distance();

	protected:
		static void run(HC_SR04 *);
		virtual int32_t actionIn(PollDevice * device);
		virtual int32_t actionOut(PollDevice * device);
		virtual int32_t actionError(PollDevice * device);
		
		// nanosecond
		std::chrono::time_point<std::chrono::high_resolution_clock> _timestamp_rising;
		std::chrono::time_point<std::chrono::high_resolution_clock> _timestamp_falling;
		Gpio * _out;
		Gpio * _in;
		std::thread * _thread;
		int32_t _fin, _status, _intervalle_500ms;
		double _distance;
};

#endif /* HC_SR04_H */
