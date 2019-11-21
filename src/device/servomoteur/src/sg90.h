#ifndef SG90_H
#define SG90_H

#include "batratypes.h"

class PCA9685;
class SG90
{
public:
	SG90(PCA9685 * pwm);
	virtual ~SG90();

	virtual void rotation(u8 port, s16 angle);

protected:
	PCA9685 *_pwm;
};

#endif
