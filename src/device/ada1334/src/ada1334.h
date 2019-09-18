#ifndef ADA1334_H
#define ADA1334_H

#include "gpiofactory.h"
#include <string>
#include <cstdint>

class I2C;
class TCS34725;
class ADA1334 : public GpioFactory
{
	public:
		ADA1334(const std::string & gpio_dev, int32_t LED_PIN, int32_t IRQ_PIN, I2C * i2c_bus);
		virtual ~ADA1334();
		
		virtual void led(uint8_t on);

	protected:
		virtual int32_t actionIn(PollDevice * device);
		virtual int32_t actionOut(PollDevice * device);
		virtual int32_t actionError(PollDevice * device);
	
		TCS34725 * capteur_lumiere;
		int32_t LED_PIN;
		int32_t IRQ_PIN;
};

#endif /* ADA1334_H */
