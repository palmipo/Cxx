#ifndef PHAT_ENVIRO_H
#define PHAT_ENVIRO_H

#include "devicei2c.h"

/* i2c_addr = 0x1d / 0x29 / 0x49 / 0x77 */
/* gpio = 4 */

//~ class I2C;
class RaspiGpio;
class PHatEnviro
{
	public:
		PHatEnviro(RaspiGpio *);
		~PHatEnviro();
	
		void setLed(uint8_t);
	
	protected:
		RaspiGpio * _gpio_led;
};

#endif /* PHAT_ENVIRO_H */
