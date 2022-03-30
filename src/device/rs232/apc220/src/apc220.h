#ifndef APC220_H
#define APC220_H

#include <cstdint>

class CtrlPIA;
class CtrlUART;
class APC220
{
	public:
		APC220(CtrlPIA *, CtrlUART *);
		virtual ~APC220();
	
		void setConfig(int32_t, int32_t, int32_t, int32_t, int32_t);
		void getConfig();
		int32_t read(uint8_t*, int32_t);
		int32_t write(uint8_t*, int32_t);

	protected:
		// SET, EN, AUX
		CtrlPIA * _pin;
		CtrlUART * _uart;
};

#endif
	
