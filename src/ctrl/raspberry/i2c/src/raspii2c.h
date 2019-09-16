#ifndef RASPI_I2C_H
#define RASPI_I2C_H

#include "i2c.h"

class RaspiI2C : public I2C
{
public:
	RaspiI2C(const char *);
	virtual ~RaspiI2C();

	virtual void setOwnAddress (uint8_t own_address);

	virtual void set (uint8_t addr, uint8_t* buf, int32_t len);
	virtual void get (uint8_t addr, uint8_t* buf, int32_t len);
	virtual void transfert (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len);

private:
	int _fd;
};

#endif /* RASPI_I2C_H */
