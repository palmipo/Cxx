#ifndef APC220_H
#define APC220_H

#include <cstdint>

class PIA;
class RS232;
class APC220
{
	public:
		APC220(PIA *, RS232 *);
		virtual ~APC220();
	
		void setConfig(int32_t, int32_t, int32_t, int32_t, int32_t);
		void getConfig();
		int32_t read(uint8_t*, int32_t);
		int32_t write(uint8_t*, int32_t);

	protected:
		// SET, EN, AUX
		PIA * _pin;
		RS232 * _uart;
};

#endif
	
