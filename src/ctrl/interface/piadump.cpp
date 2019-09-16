#include "piadump.h"
#include <iostream>

PIADump::PIADump()
: PIA()
{
}

PIADump::~PIADump()
{
}


void PIADump::set(u8 port, u8 value)
{
	std::cout << "PIADUMP::set(" << (int)port << ", " << (int)value << ")" << std::endl;
}

u8 PIADump::get(u8 port)
{
	std::cout << "PIADUMP::get(" << (int)port << ") = 0" << std::endl;
	return 0;
}

