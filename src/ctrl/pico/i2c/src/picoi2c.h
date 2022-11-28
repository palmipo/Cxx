#ifndef PICO_I2C_H
#define PICO_I2C_H

#include "ctrli2c.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

class PicoI2C : public CtrlI2C
{
public:
	PicoI2C (i2c_inst_t *, uint32_t, uint32_t);
	virtual ~PicoI2C();

	virtual void set (uint8_t, uint8_t*, int32_t);
	virtual void get (uint8_t, uint8_t*, int32_t);
	virtual void transfert (uint8_t, uint8_t*, int32_t, uint8_t*, int32_t);

private:
	i2c_inst_t * _fd;
};

#endif /* RASPI_I2C_H */
