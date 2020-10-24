#ifndef BMP280_H
#define BMP280_H

#include "devicei2c.h"

/* i2c_addr = 0xEC */

class I2C;
class BMP280 : public DeviceI2C
{
	public:
		BMP280(uint8_t, I2C *);

		void init(uint8_t osrs_t, uint8_t osrs_p, uint8_t mode, uint8_t t_sb, uint8_t filter);
		uint8_t id();
		void reset();
		uint8_t status();
		//~ void measure(double *, double *);
		//~ void measure_int32(int32_t *, int32_t *);

	protected:
		//~ int32_t dig_T1;
		//~ int32_t dig_T2;
		//~ int32_t dig_T3;
		//~ int32_t dig_P1;
		//~ int32_t dig_P2;
		//~ int32_t dig_P3;
		//~ int32_t dig_P4;
		//~ int32_t dig_P5;
		//~ int32_t dig_P6;
		//~ int32_t dig_P7;
		//~ int32_t dig_P8;
		//~ int32_t dig_P9;
		//~ int32_t dig_H1;
		//~ int32_t dig_H2;
		//~ int32_t dig_H3;
		//~ int32_t dig_H4;
		//~ int32_t dig_H5;
		//~ int32_t dig_H6;
		//~ int32_t t_fine;
		
		//~ double bmp280_compensate_T(int32_t adc_T);
		//~ double bmp280_compensate_P(int32_t adc_P);

		//~ int32_t t_fine_int32;
		//~ int32_t bmp280_compensate_T_int32(int32_t adc_T);
		//~ uint32_t bmp280_compensate_P_int32(int32_t adc_P);

};

#endif /* BMP280_H */
