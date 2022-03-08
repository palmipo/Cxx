#include "ds1621.h"
#include "ctrli2c.h"
#include "i2cexception.h"

#define DS1621_ADDRESS			0x48
#define DS1621_COMMAND_READ_TEMPERATURE	0xAA
#define DS1621_COMMAND_ACCESS_TH	0xA1
#define DS1621_COMMAND_ACCESS_TL	0xA2
#define DS1621_COMMAND_ACCESS_CONFIG	0xAC
#define DS1621_COMMAND_READ_COUNTER	0xA8
#define DS1621_COMMAND_READ_SLOPE	0xA9
#define DS1621_COMMAND_START_CONVERT	0xEE
#define DS1621_COMMAND_STOP_CONVERT	0x22

#define DS1621_CONTROL_REGISTER_DONE	7
#define DS1621_CONTROL_REGISTER_THF	6
#define DS1621_CONTROL_REGISTER_TLF	5
#define DS1621_CONTROL_REGISTER_NVB	4
#define DS1621_CONTROL_REGISTER_POL	1
#define DS1621_CONTROL_REGISTER_1SHOT	0

DS1621::DS1621(uint8_t adresse, CtrlI2C * i2c)
: DeviceI2C(DS1621_ADDRESS | (adresse & 0x7), i2c)
{}

DS1621::~DS1621()
{}
	
void DS1621::setThermostatOutputSignal (uint8_t valeur)
{
	uint8_t cpt = 0;
	uint8_t twi_snd_buffer[3];
	uint8_t twi_rcv_buffer[2];
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_CONFIG;
	_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
	while ((cpt < 100) && (DS1621_CONTROL_REGISTER_NVB == (DS1621_CONTROL_REGISTER_NVB & twi_rcv_buffer[0])))
	{
		// Util::sleep(1);
		_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
		++cpt;
	}

	uint8_t ctrl_register = twi_rcv_buffer[0] & ~(1 << DS1621_CONTROL_REGISTER_POL) | ((valeur & 0x01) << DS1621_CONTROL_REGISTER_POL);

	// configuration capteur temperature
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_CONFIG;
	twi_snd_buffer[1] = ctrl_register;
	_twi->set(_address, twi_snd_buffer, 2);
}

void DS1621::seuil_inferieur_thermostat (uint8_t valeur)
{
	uint8_t cpt = 0;
	uint8_t twi_snd_buffer[3];
	uint8_t twi_rcv_buffer[2];
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_CONFIG;
	_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
	while ((cpt < 100) && (DS1621_CONTROL_REGISTER_NVB == (DS1621_CONTROL_REGISTER_NVB & twi_rcv_buffer[0])))
	{
		// Util::sleep(1);
		_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
		++cpt;
	}

	// seuil inferieur capteur temperature
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_TL;
	twi_snd_buffer[1] = valeur;
	twi_snd_buffer[2] = 0;
	_twi->set(_address, twi_snd_buffer, 3);
}

void DS1621::seuil_superieur_thermostat (uint8_t valeur)
{
	uint8_t cpt = 0;
	uint8_t twi_snd_buffer[3];
	uint8_t twi_rcv_buffer[2];
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_CONFIG;
	_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
	while ((cpt < 100) && (DS1621_CONTROL_REGISTER_NVB == (DS1621_CONTROL_REGISTER_NVB & twi_rcv_buffer[0])))
	{
		// Util::sleep(1);
		_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
		++cpt;
	}

	// seuil superieur capteur temperature
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_TH;
	twi_snd_buffer[1] = valeur;
	twi_snd_buffer[2] = 0;
	_twi->set(_address, twi_snd_buffer, 3);
}

void DS1621::conversion_unique (uint8_t valeur)
{
	uint8_t cpt = 0;
	uint8_t twi_snd_buffer[3];
	uint8_t twi_rcv_buffer[2];
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_CONFIG;
	_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
	while ((cpt < 100) && (DS1621_CONTROL_REGISTER_NVB == (DS1621_CONTROL_REGISTER_NVB & twi_rcv_buffer[0])))
	{
		// Util::sleep(1);
		_twi->transfer(_address, twi_snd_buffer, 1, twi_rcv_buffer, 1);
		++cpt;
	}

	uint8_t ctrl_register = twi_rcv_buffer[0] & ~(1 << DS1621_CONTROL_REGISTER_1SHOT) | ((valeur & 0x01) << DS1621_CONTROL_REGISTER_1SHOT);

	// debut conversion capteur temperature
	twi_snd_buffer[0] = DS1621_COMMAND_ACCESS_CONFIG;
	twi_snd_buffer[1] = ctrl_register;
	_twi->set(_address, twi_snd_buffer, 2);
}

void DS1621::debut_conversion ()
{
	// debut conversion capteur temperature
	uint8_t twi_snd_buffer;
	twi_snd_buffer = DS1621_COMMAND_START_CONVERT;
	_twi->set(_address, &twi_snd_buffer, 1);
}

void DS1621::fin_conversion ()
{
	// fin conversion capteur temperature
	uint8_t twi_snd_buffer;
	twi_snd_buffer = DS1621_COMMAND_STOP_CONVERT;
	_twi->set(_address, &twi_snd_buffer, 1);
}

uint8_t DS1621::lecture_temperature ()
{
	// si conversion terminee
	uint8_t twi_snd_buffer;
	uint8_t twi_rcv_buffer[2];
	uint8_t cpt = 0;
	twi_snd_buffer = DS1621_COMMAND_ACCESS_CONFIG;
	_twi->transfer(_address, &twi_snd_buffer, 1, twi_rcv_buffer, 1);
	while ((cpt < 100) && (0 == (DS1621_CONTROL_REGISTER_DONE & twi_rcv_buffer[0])))
	{
		//~ Util::sleep(1);
		_twi->transfer(_address, &twi_snd_buffer, 1, twi_rcv_buffer, 1);
		++cpt;
	}

	// lecture de la temperature
	twi_snd_buffer = DS1621_COMMAND_READ_TEMPERATURE;
	_twi->transfer (_address, &twi_snd_buffer, 1, twi_rcv_buffer, 2);
	uint8_t tr = twi_rcv_buffer[0];
	
	// lecture du counter
	twi_snd_buffer = DS1621_COMMAND_READ_COUNTER;
	_twi->transfer (_address, &twi_snd_buffer, 1, twi_rcv_buffer, 1);
	uint8_t counter = twi_rcv_buffer[0];

	// lecture du slope
	twi_snd_buffer = DS1621_COMMAND_READ_SLOPE;
	_twi->transfer (_address, &twi_snd_buffer, 1, twi_rcv_buffer, 1);
	uint8_t slope = twi_rcv_buffer[0];

	// calcul de la temperature
	return (tr + ((slope - counter) / slope));
}
