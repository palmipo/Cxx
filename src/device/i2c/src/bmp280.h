#ifndef BMP280_H
#define BMP280_H

#include "devicei2c.h"

/* i2c_addr = 0x77 */

class CtrlI2C;
class BMP280 : public DeviceI2C
{
	public:
		BMP280(uint8_t, CtrlI2C *);

		uint8_t id();

		void reset();

		uint8_t status(uint8_t * = 0, uint8_t * = 0);

		void start();
		void stop();
		void one_measure();

		void read_coefficients();
		void set_sampling(uint8_t, uint8_t, uint8_t, uint8_t);

		void raw_measure(uint32_t *, uint32_t *);
		void compensate(int32_t);
		void compensate(int32_t, int32_t);

		int64_t temperature;
		int64_t pressure;

	protected:
		int64_t dig_T1;
		int64_t dig_T2;
		int64_t dig_T3;
		int64_t dig_P1;
		int64_t dig_P2;
		int64_t dig_P3;
		int64_t dig_P4;
		int64_t dig_P5;
		int64_t dig_P6;
		int64_t dig_P7;
		int64_t dig_P8;
		int64_t dig_P9;

		void set_mode(uint8_t);
};

#endif /* BMP280_H */

