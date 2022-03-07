#ifndef SPI_H
#define SPI_H

#include <cstdint>

class SPI
{
public:
	SPI()
	{}

	virtual void set (uint8_t addr, uint8_t* buf, int32_t len) = 0;
	virtual void get (uint8_t addr, uint8_t* buf, int32_t len) = 0;
	virtual void transfer (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len) = 0;
};

#endif /* SPI_H */
