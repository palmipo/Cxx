#ifndef ADA1334_H
#define ADA1334_H

#include <cstdint>

class I2C;
class PIA;
class TCS34725;
class ADA1334
{
	public:
		ADA1334(PIA *, PIA *, I2C *);
		virtual ~ADA1334();

		virtual void led(uint8_t on);

	protected:
		virtual int32_t event(PollDevice *);

		TCS34725 * _capteur_lumiere;
		PIA * _led;
		PIA * _irq;
};

#endif /* ADA1334_H */
