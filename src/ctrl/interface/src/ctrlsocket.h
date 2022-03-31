#ifndef CTRLSOCKET_H
#define CTRLSOCKET_H

#include "device.h"
#include <cstdint>

class CtrlSOCKET : public Device
{
public:
	CtrlSOCKET()
	: Device(Device::DeviceType_SOCKET)
	{}

	virtual ~CtrlSOCKET()
	{}

	virtual int32_t read(uint8_t *, int32_t) = 0;
	virtual int32_t write(uint8_t *, int32_t) = 0;
};

#endif /* CTRLSOCKET_H */
