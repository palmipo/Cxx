#include "sabertooth.h"
#include "rs232.h"
#include "moteurcc.h"

Sabertooth::Sabertooth(RS232 *ctrl)
: _uart(ctrl)
, _nb_moteurs(2)
, _moteurs(0)
{
	_moteurs = new MoteurCC[_nb_moteurs];

	// arret des moteurs
	stop();
}

Sabertooth::~Sabertooth()
{
	// arret des moteurs
	//~ stop();

	delete[] _moteurs;
}

MoteurCC *Sabertooth::getMoteur(u8 num)
{
	return &_moteurs[num&0x01];
}

void Sabertooth::stop()
{
	u8 msg = 0;
	_uart->set((s8*)&msg, 1);
}

void Sabertooth::action()
{
	u8 *msg = new u8[_nb_moteurs];

	for (int i=0; i<_nb_moteurs; ++i)
	{
		msg[i] = (i << 7) | _moteurs[i].getValue();
	}
	
	_uart->set((s8*)msg, _nb_moteurs);

	delete[] msg;
}

void Sabertooth::action(u8 num)
{
	u8 msg = (num << 7) | _moteurs[num].getValue();
	
	_uart->set((s8*)&msg, 1);
}
