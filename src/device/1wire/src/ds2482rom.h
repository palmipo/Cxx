#ifndef DS2482_ROM_H
#define DS2482_ROM_H

#include "batratypes.h"

class DS2482_ROM
{
public:
	DS2482_ROM();
	virtual ~DS2482_ROM();

	virtual u8 bit(u8 bit);
	virtual void setBit(u8 bit, u8 valeur);

	virtual u8 nbConflit();
	virtual u8 conflit(u8 bit);
	virtual void setConflit(u8 bit);

	virtual void dump();
	virtual u8 rom(u8 octet);

	virtual void setRom(u8 octet, u8 valeur);

	u8 preparerROM(DS2482_ROM * src);

protected:
	u8 _rom[8];
	u8 _nb_conflit;
	u8 _bit_conflit[8];
};

#endif
