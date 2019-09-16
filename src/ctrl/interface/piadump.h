#ifndef PIA_DUMP_H
#define PIA_DUMP_H

#include "pia.h"

class PIADump : public PIA
{
public:
	PIADump();
	virtual ~PIADump();
	
	virtual void set(u8 port, u8 value);
	virtual u8 get(u8 port = 0);
};

#endif
