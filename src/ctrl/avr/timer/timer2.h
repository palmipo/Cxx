/*
 * timer.h
 *
 * Created: 21/12/2012 15:29:05
 *  Author: toff
 */ 


#ifndef __TIMER2_H_
#define __TIMER2_H_

#include "batratypes.h"

class Timer2
{
public:
Timer2();
~Timer2();

void setTimeOutCallback(void (*callback)(void));
void setOverFlowCallback(void (*callback)(void));

//~ mode 0 : normal operation, OC0 disconnected
//~ mode 1 : Toggle OC0 on compare match
//~ mode 2 : clear OC0 on compare match
//~ mode 3 : set OC0 on compare match
void setCompareOutputMode(u8 mode);
void setCompareValue(u8 value);
void setRisingEdgeExternalClock();
void setFailingEdgeExternalClock();

//~ 0 : timer off
//~ 1 : precaler = 1
//~ 2 : prescaler = 8
//~ 3 : prescaler = 64
//~ 4 : prescaler = 256
//~ 5 : prescaler = 1024
void setPrescaler(u8 freq);
void normalWaveForm();
void ctcWaveForm();
void pwmWaveForm();
void fastPWMWaveForm();
};

#endif /* TIMER2_H_ */
