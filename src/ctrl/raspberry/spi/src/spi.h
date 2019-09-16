#ifndef SPI_H
#define SPI_H

#include "batratypes.h"

class SPI
{
public:
	SPI(const s8 *);
	~SPI();

	//~ SPI_CPOL    - Clock polarity
	//~ SPI_CPHA    - Clock phase
	//~ SPI_CS_HIGH - Chip Select active high
	//~ SPI_NO_CS   - 1 device per bus, no Chip Select
	//~ SPI_3WIRE   - Bidirectional mode, data in and out pin shared
	virtual void setMode(u32);

	//~ cdiv    speed
	//~ 2    125.0 MHz
	//~ 4     62.5 MHz
	//~ 8     31.2 MHz
	//~ 16     15.6 MHz
	//~ 32      7.8 MHz
	//~ 64      3.9 MHz
	//~ 128     1953 kHz
	//~ 256      976 kHz
	//~ 512      488 kHz
	//~ 1024      244 kHz
	//~ 2048      122 kHz
	//~ 4096       61 kHz
	//~ 8192     30.5 kHz
	//~ 16384     15.2 kHz
	//~ 32768     7629 Hz
	virtual void setClockRate(u32);

	//~ 8 - Normal
	//~ 9 - This is supported using LoSSI mode.
	virtual void setBitPerWord(u32);

	virtual void set(u8 *, u32);
	virtual void get(u8 *, u32);
	virtual void transfer(u8 *, u8 *, u32);

protected:
	s32 _fd;
	u32 _speed;
	u32 _bit_per_word;
};

#endif /* SPI_H */
