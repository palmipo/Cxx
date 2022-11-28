#include "picoi2c.h"

// i2c0 or i2c1
// PICO_DEFAULT_I2C_SDA_PIN
// PICO_DEFAULT_I2C_SCL_PIN
PicoI2C::PicoI2C(i2c_inst_t * i2c, uint32_t pin_sda, uint32_t pin_scl)
: CtrlI2C(), _fd(i2c)
{
	i2c_init(_fd, 100000);
	gpio_set_function(pin_sda, GPIO_FUNC_I2C);
	gpio_set_function(pin_scl, GPIO_FUNC_I2C);
	gpio_pull_up(pin_sda);
	gpio_pull_up(pin_scl);
}

PicoI2C::~PicoI2C()
{
	i2c_deinit(_fd);
}

void PicoI2C::set(uint8_t addr, uint8_t * buf, int32_t len)
{
	i2c_write_blocking(_fd, addr, buf, len, false);
}

void PicoI2C::get(uint8_t addr, uint8_t * buf, int32_t len)
{
	i2c_read_blocking(_fd, addr, buf, len, false);
}

void PicoI2C::transfert(uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len)
{
	i2c_write_blocking(_fd, addr, cmd, cmd_len, true);
	i2c_read_blocking(_fd, addr, buf, buf_len, false);
}
