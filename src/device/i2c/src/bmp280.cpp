#include "bmp280.h"
#include "i2c.h"
#include "log.h"
#include <thread>
#include <sstream>

BMP280::BMP280(uint8_t addr, I2C * i2c_ctrl)
: DeviceI2C(0x77 | (addr & 0x1), i2c_ctrl)
{}

void BMP280::set_sampling(uint8_t osrs_t, uint8_t osrs_p, uint8_t t_sb, uint8_t filter)
{
	uint8_t mode = 0;
	uint8_t spi3w_en = 0;
	uint8_t buffer[3];

	/* register himidity, config, control */
	buffer[0] = 0xF4;
	buffer[1] = ((osrs_t & 0x7) << 5) | ((osrs_p & 0x7) << 2) | (mode & 0x3);
	buffer[2] = ((t_sb & 0x7) << 5) | ((filter & 0x7) << 2) | (spi3w_en ? 0x1 : 0x0);
	_twi->set (_address, buffer, 3);
}

void BMP280::read_coefficients()
{
	/* register dig */
	uint8_t cmd = 0x88;
	uint8_t buffer[24];
	_twi->transfert (_address, &cmd, 1, buffer, 24);
	dig_T1 = buffer[0] | (buffer[1] << 8);
	dig_T2 = buffer[2] | (buffer[3] << 8);
	dig_T3 = buffer[4] | (buffer[5] << 8);
	dig_P1 = buffer[6] | (buffer[7] << 8);
	dig_P2 = buffer[8] | (buffer[9] << 8);
	dig_P3 = buffer[10] | (buffer[11] << 8);
	dig_P4 = buffer[12] | (buffer[13] << 8);
	dig_P5 = buffer[14] | (buffer[15] << 8);
	dig_P6 = buffer[16] | (buffer[17] << 8);
	dig_P7 = buffer[18] | (buffer[19] << 8);
	dig_P8 = buffer[20] | (buffer[21] << 8);
	dig_P9 = buffer[22] | (buffer[23] << 8);
}

uint8_t BMP280::id()
{
	uint8_t cmd = 0xD0;
	uint8_t buffer;
	_twi->transfert (_address, &cmd, 1, &buffer, 1);

	return buffer;
}

void BMP280::reset()
{
	uint8_t cmd[2] = { 0xE0, 0xB6 };
	_twi->set (_address, cmd, 2);
	
	/* attendre 300 ms */
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

uint8_t BMP280::status(uint8_t * measuring, uint8_t * m_update)
{
	uint8_t cmd = 0xF3;
	uint8_t buffer;
	_twi->transfert (_address, &cmd, 1, &buffer, 1);

	if (measuring)
	{
		*measuring = (buffer & (1<<3)) >> 3;
	}

	if (m_update)
	{
		*m_update = buffer & 1;
	}

	return buffer;
}

void BMP280::set_mode(uint8_t mode)
{
	uint8_t registre = 0xF4;
	uint8_t valeur;
	_twi->transfert (_address, &registre, 1, &valeur, 1);

	/* register control => MODE_SLEEP */
	uint8_t buffer[2];
	buffer[0] = 0xF4;
	buffer[1] = (valeur & ~(0x03)) | (mode & 0x3);
	_twi->set (_address, buffer, 2);
}

void BMP280::start()
{
	set_mode(0x03);
}

void BMP280::stop()
{
	set_mode(0x00);
}

void BMP280::one_measure()
{
	set_mode(0x01);
}

void BMP280::raw_measure(uint32_t * temp, uint32_t * pressure)
{
	uint8_t cmd1 = 0xF7;
	uint8_t mesure[6];
	_twi->transfert (_address, &cmd1, 1, mesure, 6);
	
	*pressure = ((mesure[0] << 12) | (mesure[1] << 4) | (mesure[2] >> 4));
	*temp = ((mesure[3] << 12) | (mesure[4] << 4) | (mesure[5] >> 4));

	std::stringstream ss;
	ss << "temperature : " << *temp;
	ss << ", pression : " << *pressure;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
}

void BMP280::compensate(int32_t adc_T)
{
	int64_t var1, var2, t_fine, p;
	var1 = (((adc_T>>3) - (dig_T1<<1)) * dig_T2) >> 11;
	var2 = (((((adc_T >> 4) - dig_T1) * ((adc_T>>4) - dig_T1)) >> 12) * dig_T3) >> 14;
	t_fine = var1 + var2;
	temperature = (t_fine * 5 + 128) >> 8;
}

void BMP280::compensate(int32_t adc_T, int32_t adc_P)
{
	int64_t var1, var2, t_fine, p;
	var1 = (((adc_T>>3) - (dig_T1<<1)) * dig_T2) >> 11;
	var2 = (((((adc_T >> 4) - dig_T1) * ((adc_T>>4) - dig_T1)) >> 12) * dig_T3) >> 14;
	t_fine = var1 + var2;
	temperature = (t_fine * 5 + 128) >> 8;

	var1 = t_fine - 128000;
	var2 = var1 * var1 * dig_P6;
	var2 = var2 + ((var1 * dig_P5) << 17);
	var2 = var2 + (dig_P4 << 35);
	var1 = ((dig_P3 * var1 * var1) >> 8) + ((dig_P2 * var1) << 12);
	var1 = (((int64_t)1 << 47) * dig_P1) >> 33;
	if (var1 != 0)
	{
		p = 1048576 - adc_P;
		p = (((p << 31) - var2) * 3125) / var1;
		var1 = (dig_P9 * (p>>13) * (p>>13)) >> 25;
		var2 = (p * dig_P8) >> 19;
		p = ((p + var1 + var2) >> 8) + (dig_P7 << 4);
		pressure = p;
	}
}

