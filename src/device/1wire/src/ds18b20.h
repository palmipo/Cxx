#ifndef DS18B20_H
#define DS18B20_H

#include "batratypes.h"

const u8 DS18B20_RESOLUTION_9_BITS   = 0; // 0.5
const u8 DS18B20_RESOLUTION_10_BITS = 1; // 0.25
const u8 DS18B20_RESOLUTION_11_BITS = 2; // 0.125
const u8 DS18B20_RESOLUTION_12_BITS = 3; // 0.0625

class OneWire;
class DS18B20
{
public:

	DS18B20(OneWire *);
	virtual ~DS18B20();

	float temperature(u8 num_rom);

	void scruter(void (*callback)(u8 num_rom));

	void setConfig(u8 num_rom, u8 precision, s8 temperatureBasse, s8 temperatureHaute);

	void sauvegarderConfig(u8 num_rom);
	void restaurerConfig(u8 num_rom);

protected:
	OneWire *_ctrl;
};

#endif // DS18B20_H
