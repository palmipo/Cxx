#include "colecovision.h"
#include "ctrlpia.h"

ColecoVision::ColecoVision(CtrlPIA * out, CtrlPIA * in)
: _out(out)
, _in(in)
{}

ColecoVision::~ColecoVision()
{}

void ColecoVision::read()
{
	_out->write(1);
	_joystick = _in->read();

	_out->write(2);
	_fire = _in->read();

	_out->write(4);
	_keyboard = _in->read();
}
