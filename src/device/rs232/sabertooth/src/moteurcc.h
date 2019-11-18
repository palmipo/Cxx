#ifndef MOTEUR_CC_H
#define MOTEUR_CC_H

#include "batratypes.h"

class MoteurCC
{
public:
	MoteurCC();
	virtual ~MoteurCC();

	virtual void setDirection(s8 speed);
	virtual u8 getValue() const;

private:
	u8 _valeur;
};

#endif
