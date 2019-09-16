#include "mpu9255magneto.h"
#include "i2c.h"

MPU9255Magneto::MPU9255Magneto(I2C * bus)
: DeviceI2C(0x0C, bus)
{
	sensibility(&_sensibility_x, &_sensibility_y, &_sensibility_z);
}

MPU9255Magneto::~MPU9255Magneto()
{
}

uint8_t MPU9255Magneto::wia()
{
	uint8_t snd = 0x00;
	uint8_t rcv;
	
	_twi->transfert(_address, &snd, 1, &rcv, 1);
	
	return rcv;
}

uint8_t MPU9255Magneto::info()
{
	uint8_t snd = 0x01;
	uint8_t rcv;
	
	_twi->transfert(_address, &snd, 1, &rcv, 1);
	
	return rcv;
}

void MPU9255Magneto::status(uint8_t *data_ready, uint8_t *data_overrun, uint8_t *magnetic_sensor_overflow, uint8_t *output_bit_setting)
{
	uint8_t snd = 0x02;
	uint8_t rcv;
	_twi->transfert(_address, &snd, 1, &rcv, 1);
	
	*data_ready = (rcv & 1) ? 1 : 0;
	*data_overrun = (rcv & 2) ? 1 : 0;

	snd = 0x09;	
	_twi->transfert(_address, &snd, 1, &rcv, 1);
	*magnetic_sensor_overflow = (rcv & 0x08) ? 1 : 0;
	*output_bit_setting = (rcv & 0x10) ? 1 : 0;
}

void MPU9255Magneto::setConfig(uint8_t mode_setting, uint8_t output_bit_setting)
{
	uint8_t snd[2];
	snd[0] = 0x0A;
	snd[1] = (mode_setting & 0x0F) | ((output_bit_setting & 0x01) << 4);
	_twi->set(_address, snd, 2);
}

void MPU9255Magneto::measure(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t data_ready = 0;
	uint8_t data_overrun;
	uint8_t magnetic_sensor_overflow;
	uint8_t output_bit_setting;
	
	while (!data_ready)
	{
		status(&data_ready, &data_overrun, &magnetic_sensor_overflow, &output_bit_setting);
	}
	
	if (data_ready)
	{
		uint8_t snd = 0x03;
		uint8_t rcv[6];

		_twi->transfert(_address, &snd, 1, rcv, 6);

		*x = ((rcv[1] << 8) | rcv[0]) * (((_sensibility_x - 128) * 0.5) / 128 + 1);
		*y = ((rcv[3] << 8) | rcv[2]) * (((_sensibility_y - 128) * 0.5) / 128 + 1);
		*z = ((rcv[5] << 8) | rcv[4]) * (((_sensibility_z - 128) * 0.5) / 128 + 1);		
	}
}

void MPU9255Magneto::reset(uint8_t soft_reset)
{
	uint8_t snd[2];
	snd[0] = 0x0A;
	snd[1] = soft_reset & 0x01;
	
	_twi->set(_address, snd, 2);
}

void MPU9255Magneto::setSelfTest(uint8_t cntl)
{
	uint8_t snd[2];
	snd[0] = 0x0C;
	snd[1] = ((cntl & 0x01) << 6);
	
	_twi->set(_address, snd, 2);
}

void MPU9255Magneto::sensibility(uint8_t *x, uint8_t *y, uint8_t *z)
{
	uint8_t snd = 0x10;
	uint8_t rcv[3];
	_twi->transfert(_address, &snd, 1, rcv, 3);

	*x = rcv[0];
	*y = rcv[1];
	*z = rcv[3];
}
