#ifndef BME280_H
#define BME280_H

#include "bmp280.h"

class I2C;
class BME280 : public BMP280
{
	public:
		BME280(uint8_t, I2C *);

		void read_coefficients();
		void set_sampling(uint8_t osrs_t, uint8_t osrs_p, uint8_t t_sb, uint8_t filter, uint8_t osrs_h);

		void raw_measure(uint32_t *, uint32_t *, uint32_t *);
		void compensate(int32_t, int32_t, int32_t);

		int64_t humidity;

	protected:
		int32_t dig_H1;
		int32_t dig_H2;
		int32_t dig_H3;
		int32_t dig_H4;
		int32_t dig_H5;
		int32_t dig_H6;
};

#endif /* BME280_H */

