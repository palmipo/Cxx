#include "badmintonfactory.h"
#include "gpio.h"
#include "gpioexception.h"
#include "log.h"
#include "hc1632.h"

#include <linux/gpio.h>
#include <sstream>
#include <vector>
#include <thread>

/* 01/02/04/08/10/20/40/80 */
uint8_t chiffre[10][48] ={
  { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
};
uint8_t tiret[48] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t terrain[5][48] = {
  { 0xFF, 0xFF, 0x09, 0x00, 0x09, 0x00, 0xFF, 0xFF, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0xFF, 0xFF, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0xFF, 0xFF, 0x09, 0x00, 0xFF, 0xFF }
, { 0xFF, 0xFF, 0x00, 0x80, 0x00, 0x80, 0xFF, 0xFF, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0xFF, 0xFF, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0xFF, 0xFF, 0x00, 0x80, 0xFF, 0xFF }
, { 0xFF, 0xFF, 0x80, 0x01, 0x80, 0x01, 0xFF, 0xFF, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xFF, 0xFF, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF }
, { 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0xFF, 0xFF }
, { 0xFF, 0xFF, 0x00, 0x90, 0x00, 0x90, 0xFF, 0xFF, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0xFF, 0xFF, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0xFF, 0xFF, 0x00, 0x90, 0xFF, 0xFF }
};

const int32_t NB_POINT = 48;
const int32_t NB_MATRIX = 10;
const int32_t DROITE_PIN = 23;
const int32_t RAZ_PIN = 10;
const int32_t GAUCHE_PIN = 24;
const int32_t FIN_PIN = 9;
const int32_t DATA_PIN = 7;
const int32_t WRITE_PIN = 11;
const int32_t CS_PIN[NB_MATRIX] = { 25, 8, 12, 27, 13, 6, 17, 5, 22, 18 };
int32_t score_droit = 0;
int32_t score_gauche = 0;

BatmintonFactory::BatmintonFactory(const std::string & device)
: GpioFactory(device)
, _status(0)
{
// GPIOHANDLE_REQUEST_INPUT
// GPIOHANDLE_REQUEST_OUTPUT
// GPIOHANDLE_REQUEST_ACTIVE_LOW
// GPIOHANDLE_REQUEST_OPEN_DRAIN
// GPIOHANDLE_REQUEST_OPEN_SOURCE
	Gpio * _bt_raz = event(RAZ_PIN,GPIOEVENT_REQUEST_FALLING_EDGE);
	Gpio * _bt_droite = event(DROITE_PIN, GPIOEVENT_REQUEST_FALLING_EDGE);
	Gpio * _bt_gauche = event(GAUCHE_PIN, GPIOEVENT_REQUEST_FALLING_EDGE);

	Gpio * _data = output(DATA_PIN);
	Gpio * _write = output(WRITE_PIN);
	std::vector < Gpio * > _cs_vector;
	for (int32_t i=0; i<NB_MATRIX; ++i)
	{
		Gpio * cs = output(CS_PIN[i]);
		_cs_vector.push_back(cs);
	}

	_matrix = new HC1632(_data, _write, _cs_vector);

	_matrix->write_led_buffer(0, chiffre[score_gauche/10], NB_POINT);
	_matrix->write_led_buffer(2, chiffre[score_gauche%10], NB_POINT);
	_matrix->write_led_buffer(4, tiret, NB_POINT);
	_matrix->write_led_buffer(6, chiffre[score_droit/10], NB_POINT);
	_matrix->write_led_buffer(8, chiffre[score_droit%10], NB_POINT);

	_matrix->write_led_buffer(1, terrain[0], NB_POINT);
	_matrix->write_led_buffer(3, terrain[1], NB_POINT);
	_matrix->write_led_buffer(5, terrain[2], NB_POINT);
	_matrix->write_led_buffer(7, terrain[3], NB_POINT);
	_matrix->write_led_buffer(9, terrain[4], NB_POINT);
}

BatmintonFactory::~BatmintonFactory()
{
	delete _matrix;
}

int32_t BatmintonFactory::actionIn(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	Gpio * bt = (Gpio *)device;
	bt->actionIn();

	switch(bt->pinNumber())
	{
		case RAZ_PIN:
			Log::getLogger()->debug(__FILE__, __LINE__, "RAZ");
			score_droit = 0;
			score_gauche = 0;
			break;

		case DROITE_PIN:
			Log::getLogger()->debug(__FILE__, __LINE__, "DROITE_PIN");
			score_droit += 1;
			if (score_droit > 99)
			{
				score_droit = 0;
			}
			break;

		case GAUCHE_PIN:
			Log::getLogger()->debug(__FILE__, __LINE__, "GAUCHE_PIN");
			score_gauche += 1;
			if (score_gauche > 99)
			{
				score_gauche = 0;
			}
			break;
			
		default:
			std::stringstream ss;
			ss << "PIN " << bt->pinNumber() << " inconnue !!!";
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
			break;
	}

	_status = bt->pinNumber();
	return bt->pinNumber();
}

int32_t BatmintonFactory::status()
{
	return _status;
}

int32_t BatmintonFactory::actionOut(PollDevice * device)
{
	return device->actionOut();
}

int32_t BatmintonFactory::actionError(PollDevice * device)
{
	return device->actionError();
}

void BatmintonFactory::majAffichage()
{
	_matrix->write_led_buffer(0, chiffre[score_gauche/10], NB_POINT);
	_matrix->write_led_buffer(2, chiffre[score_gauche%10], NB_POINT);
	_matrix->write_led_buffer(6, chiffre[score_droit/10], NB_POINT);
	_matrix->write_led_buffer(8, chiffre[score_droit%10], NB_POINT);
	_status = 0;
}
