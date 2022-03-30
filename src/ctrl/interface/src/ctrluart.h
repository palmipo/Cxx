#ifndef CTRLUART_H
#define CTRLUART_H

#include "device.h"
#include <cstdint>

class CtrlUART : public Device
{
public:
	CtrlUART()
	: Device(Device::DeviceType_UART)
	{}

	virtual ~CtrlUART()
	{}

	virtual int32_t read(uint8_t *, int32_t) = 0;
	virtual int32_t write(uint8_t *, int32_t) = 0;
};

#endif /* CTRLUART_H */
