#ifndef CTRLUART_H
#define CTRLUART_H

#include "device.h"
#include <cstdint>

class CtrlUart : public Device
{
CtrlUart()
: Device(DeviceType::UART)
{}

virtual ~CtrlUart()
{}

virtual int32_t read(int8_t, int32_t) = 0;
virtual int32_t write(int8_t, int32_t) = 0;
};

#endif /* CTRLUART_H */
