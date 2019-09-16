/*
 * timer.cpp
 *
 * Created: 21/12/2012 15:10:18
 *  Author: toff
 */ 
#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif


const u8 TIMER_T0_FRONT_DESCENDANT = (1 << CS02) | (1 << CS01);
const u8 TIMER_T0_FRONT_MONTANT = (1 << CS02) | (1 << CS01) | (1 << CS00);

const u8 TIMER_OFF = 0;
const u8 TIMER_PRESCALE_1 = (1<<CS00);
const u8 TIMER_PRESCALE_8 = (1<<CS01);
const u8 TIMER_PRESCALE_64 = (1<<CS01) | (1<<CS00);
const u8 TIMER_PRESCALE_256 = (1<<CS02);
const u8 TIMER_PRESCALE_1024 = (1<<CS02) | (1<<CS00);

void (*_timer_callback)(void);
void (*_timer_overflow_callback)(void);

Timer0::Timer0()
{
	TIMSK = 0;
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;

	_timer_callback = 0;
	_timer_overflow_callback = 0;
}

Timer0::~Timer0()
{
	TIMSK = 0;
	TCCR0 = TIMER_OFF;

	_timer_callback = 0;
	_timer_overflow_callback = 0;
}

ISR(TIMER0_OVF_vect)
{
	if (_timer_overflow_callback != 0)
	{
		cli();
		_timer_overflow_callback();
		sei();
	}
}

ISR(TIMER0_COMP_vect)
{
	if (_timer_callback != 0)
	{
		cli();
		//~ TCNT0 = 0;
		_timer_callback();
		sei();
	}
}

void Timer0::setTimeOutCallback(void (*callback)(void))
{
	//u8 mask = (1<<OCIE0)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<OCIE2);
	TIMSK |= (1<<OCIE0);

	_timer_callback = callback;
}

void Timer0::setOverFlowCallback(void (*callback)(void))
{
	//u8 mask = (1<<TOIE0) | (1<<TOIE1) | (1<<TOIE2);
	TIMSK |= (1<<TOIE0);

	_timer_overflow_callback = callback;
}

//~ mode 0 : normal operation, OC0 disconnected
//~ mode 1 : Toggle OC0 on compare match
//~ mode 2 : clear OC0 on compare match
//~ mode 3 : set OC0 on compare match
void Timer0::setCompareOutputMode(u8 mode)
{
	TCCR0 &= ~((1 << COM01) | (1 << COM00));
	TCCR0 |= ((mode & 0x03) << COM00);
}

void Timer0::setCompareValue(u8 value)
{
	TCNT0 = 0;
	OCR0 = value;
}

void Timer0::setRisingEdgeExternalClock()
{
	TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
	TCCR0 |= TIMER_T0_FRONT_MONTANT;
}

void Timer0::setFailingEdgeExternalClock()
{
	TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
	TCCR0 |= TIMER_T0_FRONT_DESCENDANT;
}

//~ 0 : timer off
//~ 1 : precaler = 1
//~ 2 : prescaler = 8
//~ 3 : prescaler = 64
//~ 4 : prescaler = 256
//~ 5 : prescaler = 1024
void Timer0::setPrescaler(u8 freq)
{
	TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));

	switch (freq)
	{
		case 0:
			TCCR0 |= TIMER_OFF;
			break;
		case 1:
			TCCR0 |= TIMER_PRESCALE_1;
			break;
		case 2:
			TCCR0 |= TIMER_PRESCALE_8;
			break;
		case 3:
			TCCR0 |= TIMER_PRESCALE_64;
			break;
		case 4:
			TCCR0 |= TIMER_PRESCALE_256;
			break;
		case 5:
			TCCR0 |= TIMER_PRESCALE_1024;
			break;
	}
}

void Timer0::normalWaveForm()
{
	TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
}

void Timer0::ctcWaveForm()
{
	TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
	TCCR0 |= (1 << WGM01);
}

void Timer0::pwmWaveForm()
{
	TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
	TCCR0 |= (1 << WGM00);
}

void Timer0::fastPWMWaveForm()
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01);
}
