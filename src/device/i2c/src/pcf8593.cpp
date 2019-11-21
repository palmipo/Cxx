#include "pcf8593.h"
#include "i2c.h"

#define PCF8593_CONTROL_REGISTER		0x00
#define PCF8593_ALARM_CONTROL_REGISTER	0x08

#define PCF8593_ALARM_ENABLE			2
#define PCF8593_FONCTION_MODE			4

PCF8593::PCF8593(uint8_t addr, I2C * i2c)
: DeviceI2C(0x51, i2c)
{
	uint8_t buffer[2];
	buffer[0] = PCF8593_CONTROL_REGISTER;
	buffer[1] = (0x2<<PCF8593_FONCTION_MODE);
	_twi->set(_address, buffer, 2);

	buffer[0] = PCF8593_ALARM_CONTROL_REGISTER;
	buffer[1] = 0;
	_twi->set(_address, buffer, 2);
}

void PCF8593::setAlarm()
{
	uint8_t buffer[2];
	buffer[0] = PCF8593_CONTROL_REGISTER;
	buffer[1] = (1<<PCF8593_ALARM_ENABLE);
	_twi->set(_address, buffer, 2);
}

void PCF8593::getClock(char *hh_mm_ss)
{
	uint8_t buffer[4], reg = 0x01;
	_twi->transfert(_address, &reg, 1, buffer, 4);
	hh_mm_ss[0] = ((buffer[3] & 0x30) >> 4) + '0';
	hh_mm_ss[1] = (buffer[3] & 0x0F) + '0';
	hh_mm_ss[2] = ':';
	hh_mm_ss[3] = ((buffer[2] & 0xF0) >> 4) + '0';
	hh_mm_ss[4] = (buffer[2] & 0x0F) + '0';
	hh_mm_ss[5] = ':';
	hh_mm_ss[6] = ((buffer[1] & 0xF0) >> 4) + '0';
	hh_mm_ss[7] = (buffer[1] & 0x0F) + '0';
	hh_mm_ss[8] = 0;
}

void PCF8593::setClock(const char *hh_mm_ss)
{
	uint8_t buffer[5];
	buffer[0] = 0x01;
	buffer[1] = 0x00;
	buffer[2] = (((hh_mm_ss[6] - '0') & 0x0F) << 4) & ((hh_mm_ss[7] - '0') & 0x0F);
	buffer[3] = (((hh_mm_ss[3] - '0') & 0x0F) << 4) & ((hh_mm_ss[4] - '0') & 0x0F);
	buffer[4] = (((hh_mm_ss[0] - '0') & 0x03) << 4) & ((hh_mm_ss[1] - '0') & 0x0F);
	_twi->set(_address, buffer, 5);
}

void PCF8593::setDate(const char *jj_mm_aaaa)
{
	uint8_t buffer[4];
	buffer[0] = 0x05;
	buffer[1] = (((jj_mm_aaaa[6] - '0') & 0x03) << 6) & (((jj_mm_aaaa[8] - '0') & 0x03) << 4) & ((jj_mm_aaaa[9] - '0') & 0x0F);
	buffer[2] = (((jj_mm_aaaa[3] - '0') & 0x01) << 4) & ((jj_mm_aaaa[4] - '0') & 0x0F);
	buffer[3] = (((jj_mm_aaaa[0] - '0') & 0x0F) << 4) & ((jj_mm_aaaa[1] - '0') & 0x0F);
	_twi->set(_address, buffer, 4);
}

void PCF8593::setAlarmClock(const char *hh_mm_ss)
{
	uint8_t buffer[5];
	buffer[0] = 0x09;
	buffer[1] = 0;
	buffer[2] = (((hh_mm_ss[0] - '0') & 0x03) << 4) & ((hh_mm_ss[1] - '0') & 0x0F);
	buffer[3] = (((hh_mm_ss[3] - '0') & 0x0F) << 4) & ((hh_mm_ss[4] - '0') & 0x0F);
	buffer[4] = (((hh_mm_ss[6] - '0') & 0x0F) << 4) & ((hh_mm_ss[7] - '0') & 0x0F);
	_twi->set(_address, buffer, 5);
}

void PCF8593::setAlarmDate(const char *jj_mm_aaaa)
{
	uint8_t buffer[4];
	buffer[0] = 0x0D;
	buffer[1] = (((jj_mm_aaaa[6] - '0') & 0x03) << 6) & (((jj_mm_aaaa[8] - '0') & 0x03) << 4) & ((jj_mm_aaaa[9] - '0') & 0x0F);
	buffer[2] = (((jj_mm_aaaa[3] - '0') & 0x01) << 4) & ((jj_mm_aaaa[4] - '0') & 0x0F);
	buffer[3] = (((jj_mm_aaaa[0] - '0') & 0x0F) << 4) & ((jj_mm_aaaa[1] - '0') & 0x0F);
	_twi->set(_address, buffer, 4);
}
