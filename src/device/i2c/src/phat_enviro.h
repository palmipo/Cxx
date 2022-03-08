#ifndef PHAT_ENVIRO_H
#define PHAT_ENVIRO_H

#include <cstdint>

/* i2c_addr = 0x1d / 0x29 / 0x49 / 0x77 */
/* gpio = 4 */

class PIA;
class PHatEnviro
{
	public:
		PHatEnviro(PIA *);
		~PHatEnviro();
	
		void setLed(uint8_t);
	
	protected:
		PIA * _gpio_led;
};

#endif /* PHAT_ENVIRO_H */
