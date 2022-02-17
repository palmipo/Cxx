#ifndef ONE_WIRE_ROM_H
#define ONE_WIRE_ROM_H

#include <cstdint>

class OneWireRom
{
public:
	OneWireRom();
	virtual ~OneWireRom();

	virtual uint8_t bit(uint8_t bit);
	virtual void setBit(uint8_t bit, uint8_t valeur);

	virtual uint8_t nbConflit();
	virtual uint8_t conflit(uint8_t bit);
	virtual void setConflit(uint8_t bit);

	virtual void dump();
	virtual uint8_t rom(uint8_t octet);

	virtual void setRom(uint8_t octet, uint8_t valeur);

	uint8_t preparerROM(OneWireRom * src);

protected:
	uint8_t _rom[8];
	uint8_t _nb_conflit;
	uint8_t _bit_conflit[8];
};

#endif // ONE_WIRE_ROM_H
