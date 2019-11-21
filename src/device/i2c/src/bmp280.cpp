#include "bmp280.h"
#include "i2c.h"

BMP280::BMP280(uint8_t addr, I2C * i2c_ctrl)
: DeviceI2C(0x77 | (addr & 0x1), i2c_ctrl)
{}

void BMP280::setSampling(uint8_t osrs_t, uint8_t osrs_h, uint8_t osrs_p, uint8_t mode, uint8_t t_sb, uint8_t filter)
{
	uint8_t spi3w_en = 0;
	uint8_t buffer[24];

	/* register control => MODE_SLEEP */
	buffer[0] = 0xF4;
	buffer[1] = 0x00;
	_twi->set (_address, buffer, 2);

	/* register himidity, config, control */
	buffer[0] = 0xF3;
	buffer[1] = osrs_h & 0x03;
	buffer[2] = ((t_sb & 0x7) << 5) | ((filter & 0x7) << 2) | (spi3w_en ? 0x1 : 0x0);
	buffer[3] = ((osrs_t & 0x7) << 5) | ((osrs_p & 0x7) << 2) | (mode & 0x3);
	_twi->set (_address, buffer, 4);
}

void BMP280::readCoefficients(uint8_t osrs_t, uint8_t osrs_p, uint8_t mode, uint8_t t_sb, uint8_t filter)
{
	/* register dig */
	uint8_t cmd = 0x88;
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

	/* register dig */
	cmd = 0xA1;
	_twi->transfert (_address, &cmd, 1, buffer, 1);
	dig_H1 = buffer[0];
	
	cmd = 0xE1;
	_twi->transfert (_address, &cmd, 1, buffer, 2);
	dig_H2 = buffer[0] | (buffer[1] << 8);
	
	cmd = 0xE3;
	_twi->transfert (_address, &cmd, 1, buffer, 1);
	dig_H3 = buffer[0];
	
	cmd = 0xE4;
	_twi->transfert (_address, &cmd, 1, buffer, 2);
	dig_H4 = (buffer[0] << 4) | (buffer[1] & 0xF);
	
	cmd = 0xE5;
	_twi->transfert (_address, &cmd, 1, buffer, 2);
	dig_H5 = (buffer[0] << 4) | (buffer[1] >> 4);
	
	cmd = 0xE7;
	_twi->transfert (_address, &cmd, 1, buffer, 1);
	dig_H6 = buffer[0];
}

uint8_t BMP280::id()
{
	uint8_t cmd = 0xD0;
	uint8_t buffer;
	_twi->transfert (_address, &cmd, 1, &buffer, 1);
	
	return (buffer == 0x60);
}

uint8_t BMP280::version()
{
	uint8_t cmd = 0xD1;
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

	readCorfficients();
	
	setSampling();
	
	/* attendre 100 ms */
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

uint8_t BMP280::status()
{
	uint8_t cmd = 0xF3;
	uint8_t buffer;
	_twi->transfert (_address, &cmd, 1, &buffer, 1);
	
	uint8_t measuring = buffer & (1<<3);
	uint8_t im_update = buffer & 1;
	return measuring?0:1;
}

void BMP280::measure(double * temp, double * pressure)
{
	uint8_t cmd1 = 0xF7;
	uint8_t mesure[6];
	_twi->transfert (_address, &cmd1, 1, mesure, 6);
	
	*temp = bmp280_compensate_T((mesure[0] << 12) | (mesure[1] << 4) | (mesure[2] >> 4));
	*pressure = bmp280_compensate_P((mesure[3] << 12) | (mesure[4] << 4) | (mesure[5] >> 4));
}

void BMP280::measure_int32(int32_t * temp, int32_t * pressure)
{
	uint8_t cmd1 = 0xF7;
	uint8_t mesure[6];
	_twi->transfert (_address, &cmd1, 1, mesure, 6);
	
	*temp = bmp280_compensate_T_int32((mesure[0] << 12) | (mesure[1] << 4) | (mesure[2] >> 4));
	*pressure = bmp280_compensate_P_int32((mesure[3] << 12) | (mesure[4] << 4) | (mesure[5] >> 4));
}

double BMP280::bmp280_compensate_T(int32_t adc_T)
{
	double var1, var2, T;
	var1 = (((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) *
	(((double)adc_T)/131072.0 - ((double) dig_T1)/8192.0)) * ((double)dig_T3);
	t_fine = (int32_t)(var1 + var2);
	T = (var1 + var2) / 5120.0;
	return T;
}

double BMP280::bmp280_compensate_P(int32_t adc_P)
{
	double var1, var2, p;
	var1 = ((double)t_fine/2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2/4.0)+(((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if (var1 == 0.0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 - (double)adc_P;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / 16.0;
	return p;
}

int32_t t_fine_int32;
int32_t BMP280::bmp280_compensate_T_int32(int32_t adc_T)
{
	int32_t var1, var2, T; 
	var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) * 
	((int32_t)dig_T3)) >> 14;
	t_fine_int32 = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

uint32_t BMP280::bmp280_compensate_P_int32(int32_t adc_P)
{
	int32_t var1, var2;
	uint32_t p;
	var1 = (((int32_t)t_fine_int32)>>1) - (int32_t)64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)dig_P6);
	var2 = var2 + ((var1*((int32_t)dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t)dig_P4)<<16);
	var1 = (((dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)dig_P2) * var1)>>1))>>18;
	var1 =((((32768+var1))*((int32_t)dig_P1))>>15);
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
	if (p < 0x80000000) 
	{
		p = (p << 1) / ((uint32_t)var1);
	} 
	else
	{
		p = (p / (uint32_t)var1) * 2;
	}
	var1 = (((int32_t)dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t)(p>>2)) * ((int32_t)dig_P8))>>13;
	p = (uint32_t)((int32_t)p + ((var1 + var2 + dig_P7) >> 4));
	return p;
} 
