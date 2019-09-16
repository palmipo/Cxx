#ifndef ONE_WIRE_H
#define ONE_WIRE_H

#include <cstdint>
#include "onewirerom.h"

#define NB_MAX_ROM 10

class OneWire
{
public:
	OneWire();
	~OneWire();

	// fonctions 1-wire
	virtual uint8_t oneWireReset() = 0;
	virtual uint8_t oneWireWriteBit(uint8_t bit) = 0;
	virtual uint8_t oneWireWriteByte(uint8_t byte) = 0;
	virtual uint8_t oneWireReadByte(uint8_t *byte) = 0;
	virtual uint8_t oneWireTriplet(uint8_t search_direction) = 0;

	// fonctions ROM
	uint8_t nbROM();
	void searchROM();
	void skipROM();
	void readROM();
	void writeROM(uint8_t num_rom);
	OneWireRom alarmSearch();
	OneWireRom rom(uint8_t num_rom);

	// fonctions emission / reception messages reseau
	void writeBroadcast(uint8_t *data, uint8_t length);
	void write(uint8_t num_rom, uint8_t *data, uint8_t length);
	void read(uint8_t num_rom, uint8_t *cmd, uint8_t cmd_length, uint8_t *data, uint8_t length);

	// recherche des alarmes reseau
	void scruter(void (*callback)(uint8_t num_rom));


protected:
	uint8_t _nb_rom;
	OneWireRom _rom[NB_MAX_ROM];

	virtual uint8_t status() = 0;
	virtual uint8_t readRegister() = 0;
	virtual uint8_t isBusy() = 0;

	void searchOnce(OneWireRom*);
	void searchOnceRecursif(OneWireRom*, uint8_t);

	void alarmSearchOnce(OneWireRom*);
};

#endif // ONE_WIRE_H
