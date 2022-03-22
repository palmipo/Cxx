/*
 * https://github.com/erikhagenaars/APC220/blob/master/_433_confiuration/_433_confiuration.ino
 */

#include "apc220.h"
#include "pia.h"
#include "rs232.h"
#include <iostream>
#include <sstream>

APC220::APC220(PIA * pin_set, PIA * pin_enable, PIA * pin_aux, RS232 * uart)
: _uart(uart)
, _pin_set(pin_set)
, _pin_enable(pin_enable)
, _pin_aux(pin_aux)
{
	_uart->setConfig(B9600, 8, 'N', 1, 0);
	_uart->setInterCharacterTimer(0xFF);
	_pin_set->write(1);
	_pin_enable->write(1);
	_pin_aux->write(0);
}

APC220::~APC220()
{
	_pin_set->write(0);
	_pin_enable->write(0);
}

void APC220::setConfig(int32_t frequency, int32_t air_data_rate, int32_t output_power, int32_t data_rate_in, int32_t parity)
{
	_pin_set->write(0);

	std::stringstream ss;
	ss << "WR" << (uint8_t)0x20 << "434000" << (uint8_t)0x20 << "3" << (uint8_t)0x20 << "9" << (uint8_t)0x20 << "0" << (uint8_t)0x20 << "0" << (uint8_t)0x0D << (uint8_t)0x0A;
	std::string cmd = ss.str();
	int32_t len = _uart->write((uint8_t*)cmd.c_str(), cmd.length());
	
	uint8_t msg[100];
	len = _uart->read(msg, 100);
	std::cout << __FILE__ << __LINE__ << msg << std::endl;

	_pin_set->write(1);
}

void APC220::getConfig()
{
	_pin_set->write(0);

	std::stringstream ss;
	ss << "RD" << (uint8_t)0x0D << (uint8_t)0x0A;
	std::string cmd = ss.str();
	int32_t len = _uart->write((uint8_t*)cmd.c_str(), cmd.length());
	
	uint8_t msg[100];
	len = _uart->read(msg, 100);
	std::cout << __FILE__ << __LINE__ << msg << std::endl;

	_pin_set->write(1);
}

int32_t APC220::read(uint8_t *msg, int32_t len)
{
	return _uart->read(msg, len);
}

int32_t APC220::write(uint8_t *msg, int32_t len)
{
_pin_aux->write(1);
	return _uart->write(msg, len);
_pin_aux->write(0);
}
