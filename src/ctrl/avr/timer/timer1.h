/*
 * timer.h
 *
 * Created: 21/12/2012 15:29:05
 *  Author: toff
 */ 


#ifndef __TIMER1_H_
#define __TIMER1_H_

#include "batratypes.h"

class Timer1
{
public:
	Timer1();
	~Timer1();

	void setTimeOutACallback(u16 timeout, void (*callback)(void));

	void setTimeOutBCallback(u16 timeout, void (*callback)(void));

	void setOverFlowCallback(void (*callback)(void));

	//~ 0 : timer off
	//~ 1 : precaler = 1
	//~ 2 : prescaler = 8
	//~ 3 : prescaler = 64
	//~ 4 : prescaler = 256
	//~ 5 : prescaler = 1024
	void setPrescaler(u8 freq);

	void ctcWaveForm();

	//~ mode 0 : normal operation, OC0 disconnected
	//~ mode 1 : Toggle OC0 on compare match
	//~ mode 2 : clear OC0 on compare match
	//~ mode 3 : set OC0 on compare match
	void setCompareOutputModeA(u8 mode);

	//~ mode 0 : normal operation, OC0 disconnected
	//~ mode 1 : Toggle OC0 on compare match
	//~ mode 2 : clear OC0 on compare match
	//~ mode 3 : set OC0 on compare match
	void setCompareOutputModeB(u8 mode);
};

#endif /* TIMER1_H_ */
