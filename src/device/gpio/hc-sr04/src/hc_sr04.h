#ifndef HC_SR04_H
#define HC_SR04_H

class RaspiGpio;
class PollDevice;
class HC_SR04
{
	public:
		HC_SR04(RaspiGpio *, RaspiGpio *);
		virtual ~HC_SR04();

		virtual void start(int32_t);
		virtual int32_t status();
		virtual uint64_t distance();

	protected:
		int32_t actionIn(uint32_t, uint64_t);
		
		// nanosecond
		//std::chrono::time_point<std::chrono::high_resolution_clock> _timestamp_rising;
		//std::chrono::time_point<std::chrono::high_resolution_clock> _timestamp_falling;

		RaspiGpio * _out;
		RaspiGpio * _in;
		int32_t _status;
		uint64_t _distance;
};

#endif /* HC_SR04_H */
