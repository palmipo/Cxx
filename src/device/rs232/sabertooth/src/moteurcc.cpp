#include "moteurcc.h"

MoteurCC::MoteurCC()
: _valeur(0)
{}

MoteurCC::~MoteurCC()
{}

void MoteurCC::setDirection(s8 speed)
{
	_valeur = (speed + 64) & 0x7F;
}

u8 MoteurCC::getValue() const
{
	return _valeur;
}
