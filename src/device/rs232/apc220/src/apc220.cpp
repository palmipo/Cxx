/*
 * https://github.com/erikhagenaars/APC220/blob/master/_433_confiuration/_433_confiuration.ino
 */

#include "apc220.h"
#include "ctrlpia.h"
#include "ctrluart.h"
#include "tempo.h"
#include <iostream>
#include <sstream>

int32_t SET = 0;
int32_t EN = 1;
int32_t AUX = 2;
APC220::APC220(CtrlPIA * pin, CtrlUART * uart)
: _uart(uart)
, _pin(pin)
{
	_uart->setConfig(B9600, 8, 'N', 1, 0);
	_uart->setInterCharacterTimer(0xFF);
	_pin->write((1<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(50);
}

APC220::~APC220()
{
	_pin->write((1<<SET)|(0<<EN)|(0<<AUX));
}

void APC220::setConfig(int32_t frequency, int32_t air_data_rate, int32_t output_power, int32_t data_rate_in, int32_t parity)
{
	_pin->write((0<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(10);

	std::stringstream ss;
	ss << "WR" << (uint8_t)0x20 << "434000" << (uint8_t)0x20 << "3" << (uint8_t)0x20 << "9" << (uint8_t)0x20 << "0" << (uint8_t)0x20 << "0" << (uint8_t)0x0D << (uint8_t)0x0A;
	std::string cmd = ss.str();
	int32_t len = _uart->write((uint8_t*)cmd.c_str(), cmd.length());
	
	uint8_t msg[100];
	len = _uart->read(msg, 100);
	std::cout << __FILE__ << __LINE__ << msg << std::endl;

	_pin->write((1<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(50);
}

void APC220::getConfig()
{
	_pin->write((0<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(10);

	std::stringstream ss;
	ss << "RD" << (uint8_t)0x0D << (uint8_t)0x0A;
	std::string cmd = ss.str();
	int32_t len = _uart->write((uint8_t*)cmd.c_str(), cmd.length());
	
	uint8_t msg[100];
	len = _uart->read(msg, 100);
	std::cout << __FILE__ << __LINE__ << msg << std::endl;

	_pin->write((1<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(50);
}

int32_t APC220::read(uint8_t *msg, int32_t len)
{
	_pin->write((1<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(50);

	int32_t length = _uart->read(msg, len);

	_pin->write((1<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(50);

	return length;
}

int32_t APC220::write(uint8_t *msg, int32_t len)
{
	_pin->write((1<<SET)|(1<<EN)|(1<<AUX));
	Tempo::millisecondes(50);

	int32_t length = _uart->write(msg, len);

	_pin->write((1<<SET)|(1<<EN)|(0<<AUX));
	Tempo::millisecondes(50);

	return length;
}
