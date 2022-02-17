#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device
{
	public:
		Device();
		Device(int32_t);

		virtual int32_t handler();

		bool operator==(const Device &) const;

	protected:
		int32_t _handler;

	protected:
		int32_t _max_retry;
		int32_t _timeout;
};

#endif
