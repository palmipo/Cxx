#ifndef RS485_H
#define RS485_H

#include <cstdint>

class PIA;
class Uart;
class RS485
{
public:
RS485(Uart *, PIA * = 0, PIA * = 0);
virtual ~RS485();

virtual int32_t read(uint8_t, int32_t);
virtual int32_t write(uint8_t, int32_t);

private:
Uart * _uart;
PIA * _write_pin;
PIA * _read_pin;
};

#endif /* RS485_H */
