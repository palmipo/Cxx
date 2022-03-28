#ifndef RS485_H
#define RS485_H

#include <cstdint>

class CtrlPia;
class CtrlUart;
class RS485
{
public:
RS485(CtrlUart *, CtrlPia * = 0, CtrlPia * = 0);
virtual ~RS485();

virtual int32_t read(uint8_t, int32_t);
virtual int32_t write(uint8_t, int32_t);

private:
CtrlUart * _uart;
CtrlPia * _write_pin;
CtrlPia * _read_pin;
};

#endif /* RS485_H */
