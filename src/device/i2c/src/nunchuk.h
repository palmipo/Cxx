#ifndef NUNCHUK_H_
#define NUNCHUK_H_

#include "devicei2c.h"

class I2C;
class Nunchuk : public DeviceI2C
{
public:
	Nunchuk(I2C *);

	void init();

	void lecture();

	int16_t get_joy_x_axis();
	int16_t get_joy_y_axis();
	int16_t get_accel_x_axis();
	int16_t get_accel_y_axis();
	int16_t get_accel_z_axis();

	uint8_t get_z_button();
	uint8_t get_c_button();

private:
	int16_t _joy_x_axis;
	int16_t _joy_y_axis;
	int16_t _accel_x_axis;
	int16_t _accel_y_axis;
	int16_t _accel_z_axis;

	uint8_t _z_button;
	uint8_t _c_button;

	uint8_t decode_byte (uint8_t x);
};

#endif /* NUNCHUK_H_ */
