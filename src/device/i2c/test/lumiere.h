#ifndef LUMIERE_H
#define LUMIERE_H

#include "gpiofactory.h"
#include <string>
#include <cstdint>

class I2C;
class TCS34725;
class Lumiere : public GpioFactory
{
	public:
		Lumiere(const std::string & gpio_dev, int32_t LED_PIN, int32_t IRQ_PIN, I2C * i2c_bus);
		virtual ~Lumiere();

	protected:
		virtual int32_t actionIn(PollDevice * device);
		virtual int32_t actionOut(PollDevice * device);
		virtual int32_t actionError(PollDevice * device);
	
		TCS34725 * capteur_lumiere;
		int32_t LED_PIN;
		int32_t IRQ_PIN;
};

#endif /* LUMIERE_H */
