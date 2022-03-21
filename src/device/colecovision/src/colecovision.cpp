#include "colecovision.h"

ColecoVision::ColecoVision(PIA * out, PIA * in)
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
