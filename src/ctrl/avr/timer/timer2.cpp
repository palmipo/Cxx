/*
 * timer.cpp
 *
 * Created: 21/12/2012 15:10:18
 *  Author: toff
 */ 
#include "timer2.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif


const u8 TIMER_T0_FRONT_DESCENDANT = (1 << CS22) | (1 << CS21);
const u8 TIMER_T0_FRONT_MONTANT = (1 << CS22) | (1 << CS21) | (1 << CS20);

const u8 TIMER_OFF = 0;
const u8 TIMER_PRESCALE_1 = (1<<CS20);
const u8 TIMER_PRESCALE_8 = (1<<CS21);
const u8 TIMER_PRESCALE_64 = (1<<CS21) | (1<<CS20);
const u8 TIMER_PRESCALE_256 = (1<<CS22);
const u8 TIMER_PRESCALE_1024 = (1<<CS22) | (1<<CS20);

void (*_timer2_callback)(void);
void (*_timer2_overflow_callback)(void);

Timer2::Timer2()
{
	TIMSK = 0;
	TCCR2 = 0;
	TCNT2 = 0;
	OCR2 = 0;

	_timer2_callback = 0;
	_timer2_overflow_callback = 0;
}

Timer2::~Timer2()
{
	TIMSK = 0;
	TCCR2 = TIMER_OFF;

	_timer2_callback = 0;
	_timer2_overflow_callback = 0;
}

ISR(TIMER2_OVF_vect)
{
	if (_timer2_overflow_callback != 0)
	{
		cli();
		_timer2_overflow_callback();
		sei();
	}
}

ISR(TIMER2_COMP_vect)
{
	if (_timer2_callback != 0)
	{
		cli();
		_timer2_callback();
		sei();
	}
}

void Timer2::setTimeOutCallback(void (*callback)(void))
{
	//u8 mask = (1<<OCIE0)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<OCIE2);
	TIMSK |= (1<<OCIE2);

	_timer2_callback = callback;
}

void Timer2::setOverFlowCallback(void (*callback)(void))
{
	//u8 mask = (1<<TOIE0) | (1<<TOIE1) | (1<<TOIE2);
	TIMSK |= (1<<TOIE2);

	_timer2_overflow_callback = callback;
}

//~ mode 0 : normal operation, OC0 disconnected
//~ mode 1 : Toggle OC0 on compare match
//~ mode 2 : clear OC0 on compare match
//~ mode 3 : set OC0 on compare match
void Timer2::setCompareOutputMode(u8 mode)
{
	TCCR2 &= ~((1 << COM20) | (1 << COM21));
	TCCR2 |= ((mode & 0x03) << COM20);
}

void Timer2::setCompareValue(u8 value)
{
	OCR2 = 0;
	TCNT2 = value;
}

void Timer2::setRisingEdgeExternalClock()
{
	TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));
	TCCR2 |= TIMER_T0_FRONT_MONTANT;
}

void Timer2::setFailingEdgeExternalClock()
{
	TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
	TCCR2 |= TIMER_T0_FRONT_DESCENDANT;
}

//~ 0 : timer off
//~ 1 : precaler = 1
//~ 2 : prescaler = 8
//~ 3 : prescaler = 64
//~ 4 : prescaler = 256
//~ 5 : prescaler = 1024
void Timer2::setPrescaler(u8 freq)
{
	TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));

	switch (freq)
	{
		case 0:
			TCCR2 |= TIMER_OFF;
			break;
		case 1:
			TCCR2 |= TIMER_PRESCALE_1;
			break;
		case 2:
			TCCR2 |= TIMER_PRESCALE_8;
			break;
		case 3:
			TCCR2 |= TIMER_PRESCALE_64;
			break;
		case 4:
			TCCR2 |= TIMER_PRESCALE_256;
			break;
		case 5:
			TCCR2 |= TIMER_PRESCALE_1024;
			break;
	}
}

void Timer2::normalWaveForm()
{
	TCCR2 &= ~((1 << WGM20) | (1 << WGM21));
}

void Timer2::ctcWaveForm()
{
	TCCR2 &= ~((1 << WGM20) | (1 << WGM21));
	TCCR2 |= (1 << WGM21);
}

void Timer2::pwmWaveForm()
{
	TCCR2 &= ~((1 << WGM20) | (1 << WGM21));
	TCCR2 |= (1 << WGM20);
}

void Timer2::fastPWMWaveForm()
{
	TCCR2 |= (1 << WGM20) | (1 << WGM21);
}
