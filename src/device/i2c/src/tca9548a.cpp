#include "tca9548a.h"
#include "ctrli2c.h"

TCA9548A::TCA9548A(uint8_t addr, CtrlI2C * i2c_ctrl)
: DeviceI2C(0xE0 | (addr & 0x7), i2c_ctrl)
{}

void TCA9548A::select(uint8_t channel)
{
	uint8_t buffer = 1 << channel;
	_twi->set (_address, &buffer, 1);
}
