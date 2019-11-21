#include "ds1307.h"
#include "i2c.h"
#include <cstring>

DS1307::DS1307(I2C *i2c)
: DeviceI2C(0x68, i2c)
{}

// date 18/01/73
void DS1307::setDate(const char * date)
{
	uint8_t buffer[4];
	buffer[0] = 0x04;
	buffer[1] = (((date[0] - '0') & 0x03) << 4) | ((date[1] - '0') & 0x0F);
	buffer[2] = (((date[3] - '0') & 0x01) << 4) | ((date[4] - '0') & 0x0F);
	buffer[3] = (((date[6] - '0') & 0x0F) << 4) | ((date[7] - '0') & 0x0F);
	_twi->set(_address, buffer, 4);
}

// heure 16:45:00
void DS1307::setTime(const char * time)
{
	uint8_t buffer[4];
	buffer[0] = 0x00;
	buffer[1] = (((time[6] - '0') & 0x03) << 4) | ((time[7] - '0') & 0x0F);
	buffer[2] = (((time[3] - '0') & 0x03) << 4) | ((time[4] - '0') & 0x0F);
	buffer[3] = (((time[0] - '0') & 0x01) << 4) | ((time[1] - '0') & 0x0F);
	_twi->set(_address, buffer, 4);
}

uint8_t DS1307::haltClock(uint8_t halt)
{
	uint8_t buffer[2];
	buffer[0] = 0x00;
	buffer[1] = halt ? 0x80 : 0x00;
	_twi->set(_address, buffer, 2);
}

uint8_t DS1307::clockHalted()
{
	uint8_t cmd = 0, buffer = 0;
	_twi->transfert(_address, &cmd, 1, &buffer, 1);
	
	return (buffer & 0x80) ? 1 : 0;
}

void DS1307::date(char * date)
{
	uint8_t buffer[3], adresse = 0x04;
	_twi->transfert(_address, &adresse, 1, buffer, 3);

	date[0] = ((buffer[0] & 0x30) >> 4) + '0';
	date[1] = (buffer[0] & 0x0F) + '0';
	date[2] = '/';
	date[3] = ((buffer[1] & 0x10) >> 4) + '0';
	date[4] = (buffer[1] & 0x0F) + '0';
	date[5] = '/';
	date[6] = ((buffer[2] & 0xF0) >> 4) + '0';
	date[7] = (buffer[2] & 0x0F) + '0';
	date[8] = 0;
}

void DS1307::time(char * time)
{
	uint8_t buffer[3], adresse = 0x00;
	_twi->transfert(_address, &adresse, 1, buffer, 3);

	time[0] = ((buffer[2] & 0x30) >> 4) + '0';
	time[1] = (buffer[2] & 0x0F) + '0';
	time[2] = ':';
	time[3] = ((buffer[1] & 0x70) >> 4) + '0';
	time[4] = (buffer[1] & 0x0F) + '0';
	time[5] = ':';
	time[6] = ((buffer[0] & 0x70) >> 4) + '0';
	time[7] = (buffer[0] & 0x0F) + '0';
	time[8] = 0;
}

void DS1307::setSquareWave(uint8_t frequence)
{
	uint8_t buffer[2];

	buffer[0] = 0x07;
	switch (frequence)
	{
		case 1:				// 1 Hz
		buffer[1] = 0x10;
		break;
		case 4:				// 4.096 kHz
		buffer[1] = 0x11;
		break;
		case 8:				// 8.192 kHz
		buffer[1] = 0x12;
		break;
		case 32:			// 32.768 kHz
		buffer[1] = 0x13;
		break;
		case 255:			// HIGH
		buffer[1] = 0x80;
		break;
		default:			// LOW
		buffer[1] = 0;
		break;
	}
	_twi->set(_address, buffer, 2);
}

void DS1307::setMemory(uint8_t addr, uint8_t * mem, uint32_t length)
{
	uint32_t taille = 0x08 + addr + length;
	if (taille < 0x3F)
	{
		uint8_t buffer[length+1];

		buffer[0] = addr + 0x08;
		memcpy(buffer+1, mem, length);
		_twi->set(_address, buffer, length+1);
	}
}

void DS1307::memory(uint8_t addr, uint8_t * buffer, uint32_t length)
{
	uint32_t taille = 0x08 + addr + length;
	if (taille < 0x3F)
	{
		uint8_t adresse = addr + 0x08;
		_twi->transfert(_address, &adresse, 1, buffer, length);
	}
}
