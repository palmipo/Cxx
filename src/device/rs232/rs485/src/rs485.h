#ifndef RS485_H
#define RS485_H

#include <cstdint>

class RS232;
class RS485
{
RS485(RS232 *, PIA * = 0, PIA * = 0);
virtual ~RS485();

virtual int32_t read(uint8_t, int32_t);
virtual int32_t write(uint8_t, int32_t);
};

#endif /* RS485_H */
