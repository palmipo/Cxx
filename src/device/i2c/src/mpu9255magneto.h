#ifndef MPU9255_MAGNETO_H
#define MPU9255_MAGNETO_H

#include "devicei2c.h"

#define MPU9255_MAGNETO_POWER_DOWN_MODE 0x00
#define MPU9255_MAGNETO_SINGLE_MEASURE_MODE 0x01
#define MPU9255_MAGNETO_CONTINUOUS_MODE_1 0x02
#define MPU9255_MAGNETO_CONTINUOUS_MODE_2 0x06
#define MPU9255_MAGNETO_EXTERNAL_TRIGGER_MODE 0x04
#define MPU9255_MAGNETO_SELF_TEST_MODE 0x08
#define MPU9255_MAGNETO_FUSE_ROM_ACCESS_MODE 0x0F
#define MPU9255_MAGNETO_14_BIT_OUTPUT 0x00
#define MPU9255_MAGNETO_16_BIT_OUTPUT 0x01

class I2C;
class MPU9255Magneto : public DeviceI2C
{
public:
	MPU9255Magneto(I2C * bus);
	virtual ~MPU9255Magneto();

	uint8_t wia();
	uint8_t info();
	void status(uint8_t *data_ready, uint8_t *data_overrun, uint8_t *magnetic_sensor_overflow, uint8_t *output_bit_setting);
	void setConfig(uint8_t mode_setting, uint8_t output_bit_setting);
	void measure(int16_t *x, int16_t *y, int16_t *z);
	void reset(uint8_t soft_reset);
	void setSelfTest(uint8_t cntl);
	void sensibility(uint8_t *x, uint8_t *y, uint8_t *z);

protected:
	uint8_t _sensibility_x;
	uint8_t _sensibility_y;
	uint8_t _sensibility_z;
};

#endif // MPU9255_MAGNETO_H