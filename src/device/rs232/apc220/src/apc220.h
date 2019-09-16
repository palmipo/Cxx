#ifndef APC220_H
#define APC220_H

#include "batratypes.h"

class GPIO_MOD;
class RS232;
class APC220
{
	public:
		APC220(u8, u8, RS232 *, GPIO_MOD *);
		virtual ~APC220();
	
		void setConfig(s32, s32, s32, s32, s32);
		void getConfig();
		s32 get(u8*, s32);
		s32 set(u8*, s32);

	protected:
		u8 _pin_set;
		u8 _pin_enable;
		RS232 * _uart;
		GPIO_MOD * _gpio;
};

#endif
	