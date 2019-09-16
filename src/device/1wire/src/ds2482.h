#ifndef DS2482_H
#define DS2482_H

#include "batratypes.h"
#include "onewire.h"
#include "onewirerom.h"

class I2C;
class DS2482 : public OneWire
{
public:
	DS2482(u8 addr, I2C * bus);
	~DS2482();

	// fonctions circuit
	u8 reset();
	u8 config();
	u8 setConfig(u8 highSpeed, u8 spu, u8 apu);

	// fonctions 1-wire
	u8 oneWireReset();
	u8 oneWireWriteBit(u8 bit);
	u8 oneWireWriteByte(u8 byte);
	u8 oneWireReadByte(u8 *byte);
	u8 oneWireTriplet(u8 search_direction);

protected:
	u8 _addr;
	I2C *_twi;

	u8 status();
	u8 readRegister();
	u8 isBusy();
};

#endif
