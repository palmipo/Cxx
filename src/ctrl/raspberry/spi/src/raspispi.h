#ifndef RASPISPI_H
#define RASPISPI_H

#include "spi.h"
#include <string>

class RaspiSPI: public SPI
{
public:
	RaspiSPI(const std::string &);
	~RaspiSPI();

	//~ SPI_CPOL    - Clock polarity
	//~ SPI_CPHA    - Clock phase
	//~ SPI_CS_HIGH - Chip Select active high
	//~ SPI_NO_CS   - 1 device per bus, no Chip Select
	//~ SPI_3WIRE   - Bidirectional mode, data in and out pin shared
	virtual void setMode(uint32_t);

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
	virtual void setClockRate(uint32_t);

	//~ 8 - Normal
	//~ 9 - This is supported using LoSSI mode.
	virtual void setBitPerWord(uint32_t);

	virtual void set(uint8_t *, uint32_t);
	virtual void get(uint8_t *, uint32_t);
	virtual void transfer(uint8_t *, uint8_t *, uint32_t);

protected:
	int32_t _fd;
	uint32_t _speed;
	uint32_t _bit_per_word;
};

#endif /* RASPISPI_H */
