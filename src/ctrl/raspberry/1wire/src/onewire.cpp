#include "onewire.h"
// #include "raspii2c.h"
#include <poll.h>
#include <iostream>

const uint8_t CONFIG_REG_1WS = 3;
const uint8_t CONFIG_REG_SPU = 2;
const uint8_t CONFIG_REG_APU = 0;

const uint8_t STATUS_REG_DIR = 7;
const uint8_t STATUS_REG_TSB = 6;
const uint8_t STATUS_REG_SBR = 5;
const uint8_t STATUS_REG_RST = 4;
const uint8_t STATUS_REG_LL  = 3;
const uint8_t STATUS_REG_SD  = 2;
const uint8_t STATUS_REG_PPD = 1;
const uint8_t STATUS_REG_1WB = 0;


OneWire::OneWire()
: _nb_rom(0)
{}

OneWire::~OneWire()
{}

void OneWire::searchROM()
{
	_nb_rom = 1;
	uint8_t num_rom = 0;

	while ((num_rom < _nb_rom) && (_nb_rom < NB_MAX_ROM))
	{
		searchOnce(&_rom[num_rom]);

		for (int i=0; i<_rom[num_rom].nbConflit(); i+=1)
		{
			_rom[_nb_rom].preparerROM(&_rom[num_rom]);
			_nb_rom += 1;
		}

		num_rom += 1;
	}
}

void OneWire::searchOnce(OneWireRom *rom)
{
	uint8_t presence = oneWireReset();

	if (presence)
	{
		oneWireWriteByte(0xF0);

		searchOnceRecursif(rom, 0);
	}
}

void OneWire::searchOnceRecursif(OneWireRom *rom, uint8_t num_bit)
{
	uint8_t res = oneWireTriplet(rom->bit(num_bit));

	uint8_t first_bit = (res & (1 << STATUS_REG_SBR)) ? 1 : 0;
	uint8_t second_bit = (res & (1 << STATUS_REG_TSB)) ? 1 : 0;
	uint8_t dir_bit = (res & (1 << STATUS_REG_DIR)) ? 1 : 0;

	// reponse
	if (first_bit != second_bit)
	{
		rom->setBit(num_bit, dir_bit);

		searchOnceRecursif(rom, num_bit+1);
	}
	
	// conflit
	else if (first_bit == 0)
	{
		rom->setConflit(num_bit);

		searchOnceRecursif(rom, num_bit+1);
	}
	
	// absence
	else
	{
	}
}

void OneWire::skipROM()
{
	uint8_t presence = oneWireReset();
	
	if (presence)
	{
		oneWireWriteByte(0xCC);
	}
}

OneWireRom OneWire::alarmSearch()
{
	/*
	while ((num_rom < _nb_alarm_rom) && (_nb_alarm_rom < NB_MAX_ROM))
	{
		alarmSearchOnce(_alarm_rom + num_rom);

		for (int i=0; i<_alarm_rom[num_rom].nbConflit(); i+=1)
		{
			_alarm_rom[_nb_alarm_rom].preparerROM(&_alarm_rom[num_rom]);
			_nb_alarm_rom += 1;
		}

		num_rom += 1;
	}
	*/
	OneWireRom alarm_rom;
	alarmSearchOnce(&alarm_rom);
	return alarm_rom;
}

void OneWire::alarmSearchOnce(OneWireRom *alarm_rom)
{
	uint8_t presence = oneWireReset();
	
	if (presence)
	{
		oneWireWriteByte(0xEC);
		
		uint8_t num_bit = 0;
		searchOnceRecursif(alarm_rom, num_bit);
	}
}

void OneWire::readROM()
{
	uint8_t presence = oneWireReset();
	
	if (presence)
	{
		oneWireWriteByte(0x33);
		uint8_t byte;
		for (int i=0; i<8; ++i)
		{
			oneWireReadByte(&byte);
			_rom[0].setRom(i, byte);
		}
		_nb_rom = 1;
	}
}

void OneWire::writeROM(uint8_t num_rom)
{
	uint8_t presence = oneWireReset();
	
	if (presence)
	{
		oneWireWriteByte(0x55);
		for (int i=0; i<8; ++i)
		{
			oneWireWriteByte(_rom[num_rom].rom(i));
		}
	}
}

uint8_t OneWire::nbROM()
{
	return _nb_rom;
}

OneWireRom OneWire::rom(uint8_t num_rom)
{
	if (num_rom < _nb_rom)
	{
		return _rom[num_rom];
	}
}

void OneWire::writeBroadcast(uint8_t *cmd, uint8_t cmd_length)
{
	skipROM();
	for (int i=0; i<cmd_length; ++i)
	{
		oneWireWriteByte(cmd[i]);
	}
}

void OneWire::write(uint8_t num_rom, uint8_t *cmd, uint8_t cmd_length)
{
	writeROM(num_rom);
	for (int i=0; i<cmd_length; ++i)
	{
		oneWireWriteByte(cmd[i]);
	}
}

void OneWire::read(uint8_t num_rom, uint8_t *cmd, uint8_t cmd_length, uint8_t *data, uint8_t data_length)
{
	writeROM(num_rom);
	for (int i=0; i<cmd_length; ++i)
	{
		oneWireWriteByte(cmd[i]);
	}
	
	uint8_t byte;
	for (int i=0; i<data_length; ++i)
	{
		oneWireReadByte(&byte);
		data[i] = byte;
	}
}

void OneWire::scruter(void (*callback)(uint8_t num_rom))
{
	OneWireRom alarm = alarmSearch();
	alarm.dump();
	/*
	if (callback)
	{
		callback(0);
	}
	*/
}
