#ifndef UART_H
#define UART_H

#include "device.h"
#include <cstdint>

class Uart : public Device
{
Uart()
{}

virtual ~Uart()
{}

virtual int32_t read(int8_t, int32_t) = 0;
virtual int32_t write(int8_t, int32_t) = 0;
};

#endif /* UART_H */
