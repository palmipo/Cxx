#ifndef APC220_H
#define APC220_H

#include <cstdint>

class PIA;
class RS232;
class APC220
{
	public:
		APC220(PIA *, PIA *, RS232 *);
		virtual ~APC220();
	
		void setConfig(int32_t, int32_t, int32_t, int32_t, int32_t);
		void getConfig();
		int32_t get(uint8_t*, int32_t);
		int32_t set(uint8_t*, int32_t);

	protected:
		PIA * _pin_set;
		PIA * _pin_enable;
		RS232 * _uart;
};

#endif
	