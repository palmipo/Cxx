#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device
{
	public:
		Device(Type);
		Device(Type, int32_t);

		enum { GPIO = 1, I2C, SPI, UART, SOCKET, JOYSTICK, CAN } Type;

		virtual int32_t handler();
		virtual Type type();

		bool operator==(const Device &) const;

	protected:
		int32_t _handler;
		int32_t _max_retry;
		int32_t _timeout;
		Type _type;
};

#endif
