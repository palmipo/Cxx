#ifndef RASPI_I2C_H
#define RASPI_I2C_H

#include "ctrli2c.h"

class RaspiI2C : public CtrlI2C
{
public:
	RaspiI2C(const char *);
	virtual ~RaspiI2C();

	virtual void set (uint8_t addr, uint8_t* buf, int32_t len);
	virtual void get (uint8_t addr, uint8_t* buf, int32_t len);
	virtual void transfer (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len);

private:
	int _fd;
};

#endif /* RASPI_I2C_H */
