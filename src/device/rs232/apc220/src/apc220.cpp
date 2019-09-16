/*
 * https://github.com/erikhagenaars/APC220/blob/master/_433_confiuration/_433_confiuration.ino
 */

#include "apc220.h"
#include "gpio_mod.h"
#include "rs232.h"
#include <iostream>
#include <sstream>

APC220::APC220(u8 pin_set, u8 pin_enable, RS232 * uart, GPIO_MOD * gpio)
: _gpio(gpio)
, _uart(uart)
, _pin_set(pin_set)
, _pin_enable(pin_enable)
{
	_uart->setConfig(B9600, 8, 'N', 1, 0);
	_uart->setInterCharacterTimer(0xFF);
	_gpio->setDirection(_pin_set, 0, 1);
	_gpio->setDirection(_pin_enable, 0, 1);
}

APC220::~APC220()
{
	_gpio->set(_pin_set, 0);
	_gpio->set(_pin_enable, 0);
}

void APC220::setConfig(s32 frequency, s32 air_data_rate, s32 output_power, s32 data_rate_in, s32 parity)
{
	_gpio->set(_pin_set, 0);

	std::stringstream ss;
	ss << "WR" << (u8)0x20 << "434000" << (u8)0x20 << "3" << (u8)0x20 << "9" << (u8)0x20 << "0" << (u8)0x20 << "0" << (u8)0x0D << (u8)0x0A;
	std::string cmd = ss.str();
	s32 len = _uart->set((u8*)cmd.c_str(), cmd.length());
	
	u8 msg[100];
	len = _uart->get(msg, 100);
	std::cout << __FILE__ << __LINE__ << msg << std::endl;

	_gpio->set(_pin_set, 1);
}

void APC220::getConfig()
{
	_gpio->set(_pin_set, 0);

	std::stringstream ss;
	ss << "RD" << (u8)0x0D << (u8)0x0A;
	std::string cmd = ss.str();
	s32 len = _uart->set((u8*)cmd.c_str(), cmd.length());
	
	u8 msg[100];
	len = _uart->get(msg, 100);
	std::cout << __FILE__ << __LINE__ << msg << std::endl;

	_gpio->set(_pin_set, 1);
}

s32 APC220::get(u8 *msg, s32 len)
{
	return _uart->get(msg, len);
}

s32 APC220::set(u8 *msg, s32 len)
{
	return _uart->set(msg, len);
}
