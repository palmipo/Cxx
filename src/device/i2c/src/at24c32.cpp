#include "at24c32.h"
#include "i2c.h"

AT24C32::AT24C32(I2C *i2c)
: DeviceI2C(0x50, i2c)
{}

void AT24C32::write(uint16_t addr, uint8_t * value, int32_t length)
{
	uint8_t data[ length + 2 ];
	data[ 0 ] = addr >> 8;
	data[ 1 ] = addr & 0xFF;
	for (int32_t i=0; i<length; ++i)
	{
		data[ i + 2 ] = value[i];
	}
	_twi->set(_address, data, length + 2);
}

void AT24C32::read(uint16_t addr, uint8_t * data, int32_t length)
{
	uint8_t cmd [ 2 ];
	cmd[ 0 ] = addr >> 8;
	cmd[ 1 ] = addr & 0xFF;
	_twi->transfert(_address, cmd, 2, data, length);
}
