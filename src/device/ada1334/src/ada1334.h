#ifndef ADA1334_H
#define ADA1334_H

#include <cstdint>

class CtrlI2C;
class CtrlPia;
class TCS34725;
class ADA1334
{
	public:
		ADA1334(CtrlPia *, CtrlI2C *);
		virtual ~ADA1334();

		virtual void led(uint8_t on);

	protected:
		virtual int32_t event(PollDevice *);

		TCS34725 * _capteur_lumiere;
		CtrlPia * _led;
};

#endif /* ADA1334_H */
