#include "at24c32.h"
#include "i2c.h"

AT24C32::AT24C32(I2C *i2c)
: DeviceI2C(0x50, i2c)
{}

void AT24C32::write(uint16_t addr, uint8_t value)
{
	_twi->set(_address, &value, 1);
}

uint8_t AT24C32::read(uint16_t addr)
{
	uint8_t value = 0;
	_twi->transfert(_address, (uint8_t *)&addr, 2, &value, 1);
}
