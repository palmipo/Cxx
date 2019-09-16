#ifndef SABERTOOTH_H
#define SABERTOOTH_H

#include "batratypes.h"

class RS232;
class MoteurCC;
class Sabertooth
{
public:
	Sabertooth(RS232 *ctrl);
	virtual ~Sabertooth();

	virtual MoteurCC *getMoteur(u8 num);

	virtual void stop();
	virtual void action();
	virtual void action(u8 num);

private:
	RS232 *_uart;
	u8 _nb_moteurs;
	MoteurCC *_moteurs;
};

#endif
