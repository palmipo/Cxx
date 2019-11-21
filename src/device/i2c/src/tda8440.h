#ifndef __TDA8440_H__
#define __TDA8440_H__

#include "devicei2c.h"

class I2C;
class TDA8440 : public DeviceI2C
{
public:
	TDA8440(uint8_t, I2C *);

	//~ valeurs possible pour on_off
	//~ 0 : input active
	//~ 1 : input inactive
	void setOnOff(uint8_t on_off);

	//~ valeurs possible pour audioA et audioB
	//~ 0 : aucune entree
	//~ 1 : entree 1
	//~ 2 : entree 2
	//~ 3 : entree 1 & 2
	void setAudioOutput(uint8_t audioA, uint8_t audioB);

	//~ valeurs possible pour video
	//~ 0 : aucune entree
	//~ 1 : entree 1
	//~ 2 : entree 2
	//~ 3 : entree 1 & 2
	//~ valeurs possibles pour gain
	//~ 0 : amplification de 1
	//~ 1 : amplification de 2
	void setVideoOutput(uint8_t video, uint8_t gain);
};

#endif
