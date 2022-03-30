#ifndef COLECOVISION_H
#define COLECOVISION_H

#include <cstdint>

class CtrlPIA;
class ColecoVision
{
public:
	ColecoVision(CtrlPIA *, CtrlPIA *);
	virtual ~ColecoVision();

	void read();

protected:
	CtrlPIA * _out;
	CtrlPIA * _in;
};

#endif /* COLECOVISION_H */
