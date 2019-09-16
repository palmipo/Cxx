#ifndef I2C_H
#define I2C_H

#include <cstdint>

class I2C
{
public:
	I2C()
	{}

	// virtual void setOwnAddress (uint8_t own_address) = 0;
	// virtual void read (uint8_t* buf, int32_t len) = 0;
	// virtual void write (uint8_t* buf, int32_t len) = 0;

	virtual void set (uint8_t addr, uint8_t* buf, int32_t len) = 0;
	virtual void get (uint8_t addr, uint8_t* buf, int32_t len) = 0;
	virtual void transfert (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len) = 0;
};

#endif /* I2C_H */
