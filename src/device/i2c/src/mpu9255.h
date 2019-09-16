#ifndef MPU9255_H
#define MPU9255_H

#include "devicei2c.h"

class I2C;
class MPU9255Magneto;
class MPU9255 : public DeviceI2C
{
public:
	MPU9255(I2C * bus);
	virtual ~MPU9255();

	MPU9255Magneto *magnetometre();

	int16_t temperature();

	uint8_t whoami();

protected:
	MPU9255Magneto * _magneto;
};

#endif // MPU9255_H