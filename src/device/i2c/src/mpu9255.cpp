#include "mpu9255.h"
#include "ctrli2c.h"
#include "mpu9255magneto.h"

MPU9255::MPU9255(CtrlI2C * bus)
: DeviceI2C(0x68, bus)
, _magneto(0)
{
	_magneto = new MPU9255Magneto(bus);

	// hard reset
	uint8_t snd[2];

	// SMPLRT_DIV
	snd[0] = 0x19;
	snd[1] = 0x07;
	_twi->set(_address, snd, 2);

	// PWR_MGMT_1
	snd[0] = 0x6b;
	snd[1] = 0x01;
	_twi->set(_address, snd, 2);

	// PWR_MGMT_2
	snd[0] = 0x6C;
	snd[1] = 0x00;
	_twi->set(_address, snd, 2);

	// DLPF_CFG
	snd[0] = 0x1a;
	snd[1] = 0x00;
	_twi->set(_address, snd, 2);

	// GYRO_CONFIG
	snd[0] = 0x1B;
	snd[1] = 0x00;
	_twi->set(_address, snd, 2);

	// ACCEL_CONFIG
	snd[0] = 0x1C;
	snd[1] = 0x00;
	_twi->set(_address, snd, 2);

	// INT_PIN_CFG
	snd[0] = 0x37;
	snd[1] = 0x02;
	_twi->set(_address, snd, 2);

	// CNTL
	snd[0] = 0x0a;
	snd[1] = 0x16;
	_twi->set(_address, snd, 2);
}

MPU9255::~MPU9255()
{
	delete _magneto;
}

int16_t MPU9255::temperature()
{
	uint8_t snd = 0x41;
	uint8_t rcv[2];
	
	_twi->transfer(_address, &snd, 1, rcv, 2);
	
	int16_t temperature = (rcv[0] << 8) | rcv[1];
	return temperature / 340 + 36.53;
}

MPU9255Magneto *MPU9255::magnetometre()
{
	return _magneto;
}

uint8_t MPU9255::whoami()
{
	uint8_t snd = 0x75;
	uint8_t rcv;
	
	_twi->transfer(_address, &snd, 1, &rcv, 1);
	
	return rcv;
}
