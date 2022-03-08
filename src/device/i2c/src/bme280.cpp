#include "bme280.h"
#include "ctrli2c.h"
#include "log.h"
#include <thread>
#include <sstream>

BME280::BME280(uint8_t addr, CtrlI2C * i2c_ctrl)
: BMP280(addr, i2c_ctrl)
{}

void BME280::set_sampling(uint8_t osrs_t, uint8_t osrs_p, uint8_t t_sb, uint8_t filter, uint8_t osrs_h)
{
	BMP280::set_sampling(osrs_t, osrs_p, t_sb, filter);

	/* register himidity */
	uint8_t buffer[2];
	buffer[0] = 0xF2;
	buffer[1] = osrs_h & 0x7;
	_twi->set (_address, buffer, 2);
}

void BME280::read_coefficients()
{
	BMP280::read_coefficients();

	uint8_t cmd = 0xA1;
	uint8_t buffer[8];

	_twi->transfer (_address, &cmd, 1, buffer, 1);
	dig_H1 = buffer[0];
	
	cmd = 0xE1;
	_twi->transfer (_address, &cmd, 1, buffer, 7);
	dig_H2 = buffer[0] | (buffer[1] << 8);
	dig_H3 = buffer[2];
	dig_H4 = (buffer[3] << 4) | (buffer[4] & 0x0F);
	dig_H5 = ((buffer[4] & 0xF0) >> 4) | (buffer[5] << 4);
	dig_H6 = buffer[6];
}

void BME280::raw_measure(uint32_t * temperature, uint32_t * pressure, uint32_t * humidity)
{
	uint8_t cmd = 0xF7;
	uint8_t mesure[8];
	_twi->transfer (_address, &cmd, 1, mesure, 8);

	*temperature = (mesure[0] << 12) | (mesure[1] << 4) | (mesure[2] >> 4);
	*pressure = (mesure[3] << 12) | (mesure[4] << 4) | (mesure[5] >> 4);
	*humidity = (mesure[6] << 8) | mesure[7];

	std::stringstream ss;
	ss << "raw temperature : " << *temperature << std::endl;
	ss << "raw pressure : " << *pressure << std::endl;
	ss << "raw humidity : " << *humidity << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
}

void BME280::compensate(int32_t adc_T, int32_t adc_P, int32_t adc_H)
{
	int64_t var1, t_fine;
	var1 = t_fine - 76800;
	var1 = (((((adc_H << 14) - (dig_H4 << 20) - (dig_H5 * var1)) + 16384) >> 15) * ((((((var1 * dig_H6 >> 10) + (((var1 * dig_H3)) >> 11) + 32768) >> 10) + 2097152) * dig_H2 + 8192) >> 14));
	var1 = var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * dig_H1) >> 4);
	var1 = (var1 < 0) ? 0 : var1;
	var1 = (var1 > 419430400) ? 419430400 : var1;
	humidity = var1 >> 12;
}

