#include "nunchuk.h"
#include "i2c.h"
#include <poll.h>
#include <iostream>
#include <iomanip>

/*
 * http://domoticx.com/pinout-wii-nunchuk/
 * connections to Arduino
 * gnd   -- white  -- gnd
 * +3.3V -- red    -- 3.3V
 * SDA   -- green  -- A4
 * SCK   -- yellow -- A5
 */

Nunchuk::Nunchuk(I2C *i2c)
:DeviceI2C(0x52, i2c)
{}

void Nunchuk::init()
{
	// nunchuk blanc
	std::cout << __FILE__ << __LINE__ << std::endl;
	uint8_t buffer[2];
	buffer[0] = 0x40;
	buffer[1] = 0x00;
	_twi->set(_address, buffer, 2);
	
	// nunchuk noir
	//~ std::cout << __FILE__ << __LINE__ << std::endl;
	//~ buffer[0] = 0xF0;
	//~ buffer[1] = 0x55;
	//~ _twi->set(_address, buffer, 2);
	
	//~ std::cout << __FILE__ << __LINE__ << std::endl;
	//~ buffer[0] = 0xFB;
	//~ buffer[1] = 0x00;
	//~ _twi->set(_address, buffer, 2);
}

int16_t Nunchuk::get_joy_x_axis()
{
	return _joy_x_axis;
}

int16_t Nunchuk::get_joy_y_axis()
{
	return _joy_y_axis;
}

int16_t Nunchuk::get_accel_x_axis()
{
	return _accel_x_axis;
}

int16_t Nunchuk::get_accel_y_axis()
{
	return _accel_y_axis;
}

int16_t Nunchuk::get_accel_z_axis()
{
	return _accel_z_axis;
}

uint8_t Nunchuk::get_z_button()
{
	return _z_button;
}

uint8_t Nunchuk::get_c_button()
{
	return _c_button;
}

void Nunchuk::lecture()
{
	std::cout << __FILE__ << __LINE__ << std::endl;

	uint8_t snd[2], rcv[6], buf[6];
	snd[0] = 0x00;
	//~ snd[1] = 0x08;
	_twi->set(_address, snd, 1);
	_twi->get(_address, rcv, 6);

	for (uint8_t i=0; i<6; i++)
	{
		buf[i] = decode_byte(rcv[i]);
	}

	_joy_x_axis = buf[0];
	_joy_y_axis = buf[1];

	_accel_x_axis = ((buf[2] << 2) | ((buf[5] >> 2) & 0x03));
	_accel_y_axis = ((buf[3] << 2) | ((buf[5] >> 4) & 0x03));
	_accel_z_axis = ((buf[4] << 2) | ((buf[5] >> 6) & 0x03));

	_z_button = ! (buf[5] & 0x01);
	_c_button = !((buf[5] >> 1) & 0x01);
}

uint8_t Nunchuk::decode_byte (uint8_t x)
{
	return (x ^ 0x17) + 0x17;
}
