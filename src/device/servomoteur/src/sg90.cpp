#include "sg90.h"
#include "pca9685.h"
#include "pca9685led.h"
#include <iostream>

SG90::SG90(PCA9685 * pwm)
: _pwm(pwm)
{
	_pwm->setOutDrv(1);
	_pwm->setAutoIncrement(1);
	_pwm->setPwmFrequency(50);
	_pwm->setAllLeds(0, 307);
}

SG90::~SG90()
{}

// valeur entre 1ms et 2ms.
// valeur=1.5ms => 0°
void SG90::rotation(u8 port, s16 angle)
{
	float tempo = 1.5 + 0.5 * (float)angle / 45.;
	
	float value = 4096. * tempo / 20.;
	_pwm->getLed(port)->setOffsetON(0);
	_pwm->getLed(port)->setOffsetOFF((s16)value);
	_pwm->write(port);
}
