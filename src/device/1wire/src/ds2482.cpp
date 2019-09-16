#include "ds2482.h"
#include "onewire.h"
#include "i2c.h"
#include <poll.h>
#include <iostream>

const u8 CONFIG_REG_1WS = 3;
const u8 CONFIG_REG_SPU = 2;
const u8 CONFIG_REG_APU = 0;

const u8 STATUS_REG_DIR = 7;
const u8 STATUS_REG_TSB = 6;
const u8 STATUS_REG_SBR = 5;
const u8 STATUS_REG_RST = 4;
const u8 STATUS_REG_LL  = 3;
const u8 STATUS_REG_SD  = 2;
const u8 STATUS_REG_PPD = 1;
const u8 STATUS_REG_1WB = 0;


DS2482::DS2482(u8 addr, I2C * bus)
: OneWire()
, _addr(0x18 | (addr & 0x03))
, _twi(bus)
{}

DS2482::~DS2482()
{}

u8 DS2482::reset()
{
	u8 cmd;
	cmd = 0xF0;
	u8 status_register;

	_twi->transfert(_addr, &cmd, 1, &status_register, 1);

	return ((status_register & 0xF7) == 0x10);
}

u8 DS2482::status()
{
	u8 cmd[2];
	cmd[0] = 0xE1;
	cmd[1] = 0xF0;
	u8 status_register;

	_twi->transfert(_addr, cmd, 2, &status_register, 1);

	return status_register;
}

u8 DS2482::readRegister()
{
	u8 cmd[2];
	cmd[0] = 0xE1;
	cmd[1] = 0xE1;
	u8 status_register;

	_twi->transfert(_addr, cmd, 2, &status_register, 1);

	return status_register;
}

u8 DS2482::config()
{
	u8 cmd[2];
	cmd[0] = 0xE1;
	cmd[1] = 0xC3;
	u8 cfg;

	_twi->transfert(_addr, cmd, 2, &cfg, 1);

	return cfg & 0x0F;
}

u8 DS2482::setConfig(u8 highSpeed, u8 spu, u8 apu)
{
	u8 config = (highSpeed << CONFIG_REG_1WS) | (spu << CONFIG_REG_SPU) | (apu << CONFIG_REG_APU);

	u8 cmd[2];
	cmd[0] = 0xD2;
	cmd[1] = ((~config << 4) & 0xF0) | (config & 0x0F);

	u8 cfg;

	_twi->transfert(_addr, cmd, 2, &cfg, 1);

	return (config == cfg);
}

u8 DS2482::isBusy()
{
	u8 wb;
	int loopCount = 100;
	while((wb = status() & (1 << STATUS_REG_1WB)) && (loopCount > 0))
	{
		poll(0, 0, 1);
		--loopCount;
	}
	return wb;
}

u8 DS2482::oneWireReset()
{
	u8 cmd = 0xB4;
	_twi->set(_addr, &cmd, 1);
	
	// attendre que 1WS bit passe a 0
	u8 ppd = isBusy();

	return (status() & (1 << STATUS_REG_PPD)) ? 1 : 0;
}

u8 DS2482::oneWireWriteBit(u8 bit)
{
	u8 cmd[2];
	cmd[0] = 0x87;
	cmd[1] = bit ? 0x80 : 0x00;
	_twi->set(_addr, cmd, 2);
	
	isBusy();

	return (status() & (1 << STATUS_REG_SBR)) ? 1 : 0;
}

u8 DS2482::oneWireWriteByte(u8 byte)
{
	u8 cmd[2];
	cmd[0] = 0xA5;
	cmd[1] = byte;
	
	_twi->set(_addr, cmd, 2);
	
	isBusy();

	return status();
}

u8 DS2482::oneWireReadByte(u8 *byte)
{
	u8 cmd;
	cmd = 0x96;
	
	_twi->set(_addr, &cmd, 1);

	isBusy();
	
	*byte = readRegister();
	
	return status();
}

u8 DS2482::oneWireTriplet(u8 search_direction)
{
	u8 cmd[2];
	cmd[0] = 0x78;
	cmd[1] = search_direction ? 0x80 : 0x00;
	_twi->set(_addr, cmd, 2);

	isBusy();

	return status();
}
