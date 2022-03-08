#include "tda8440.h"
#include "ctrli2c.h"
#include <cstring>

const uint8_t BIT_AUDIO_1A = 7;
const uint8_t BIT_AUDIO_2A = 6;
const uint8_t BIT_AUDIO_1B = 5;
const uint8_t BIT_AUDIO_2B = 4;
const uint8_t BIT_VIDEO_1 = 3;
const uint8_t BIT_VIDEO_2 = 2;
const uint8_t BIT_VIDEO_GAIN = 1;
const uint8_t BIT_ON_OFF = 0;

TDA8440::TDA8440(uint8_t addr, CtrlI2C *i2c)
: DeviceI2C(0x48 | (addr & 0x07), i2c)
{}

//~ valeurs possible pour on_off
//~ 0 : input active
//~ 1 : input inactive
void TDA8440::setOnOff(uint8_t on_off)
{
	uint8_t buffer;

	_twi->get(_address, &buffer, 1);
	uint8_t mask = buffer & 0xFE;
	buffer = mask | (on_off & 0x01);
	_twi->set(_address, &buffer, 1);
}

//~ valeurs possible pour audioA et audioB
//~ 0 : aucune entree
//~ 1 : entree 1
//~ 2 : entree 2
//~ 3 : entree 1 & 2
void TDA8440::setAudioOutput(uint8_t audioA, uint8_t audioB)
{
	uint8_t buffer;

	_twi->get(_address, &buffer, 1);
	uint8_t mask = buffer & 0x0F;
	buffer = mask | ((audioA & 0x03) << 6) | ((audioB & 0x03) << 4);
	_twi->set(_address, &buffer, 1);
}

//~ valeurs possible pour video
//~ 0 : aucune entree
//~ 1 : entree 1
//~ 2 : entree 2
//~ 3 : entree 1 & 2
//~ valeurs possibles pour gain
//~ 0 : amplification de 1
//~ 1 : amplification de 2
void TDA8440::setVideoOutput(uint8_t video, uint8_t gain)
{
	uint8_t buffer;

	_twi->get(_address, &buffer, 1);
	uint8_t mask = buffer & 0xF1;
	buffer = mask | ((video & 0x03) << 2) | ((gain & 0x01) << 1);
	_twi->set(_address, &buffer, 1);
}
