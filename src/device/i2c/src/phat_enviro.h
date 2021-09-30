#ifndef PHAT_ENVIRO_H
#define PHAT_ENVIRO_H

#include "devicei2c.h"

/* i2c_addr = 0x1d / 0x29 / 0x49 / 0x77 */
/* gpio = 4 */

//~ class I2C;
class Gpio;
class PHatEnviro
{
	public:
		PHatEnviro(Gpio *);
		~PHatEnviro();
	
		void setLed(uint8_t);
	
	protected:
		Gpio * _gpio_led;
};

#endif /* PHAT_ENVIRO_H */
