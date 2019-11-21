/*
 * timer.cpp
 *
 * Created: 21/12/2012 15:10:18
 *  Author: toff
 */ 
#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 1000000UL
#endif


//TCCR1A = COM1A1	COM1A0	COM1B1	COM1B0	FOC1A	FOC1B	WGM11	WGM10
//TCCR1B = ICNC1	ICES1	–-----	WGM13	WGM12	CS12	CS11	CS10

const u8 TIMER_OFF = 0;
const u8 TIMER_PRESCALE_1 = (1<<CS10);
const u8 TIMER_PRESCALE_8 = (1<<CS11);
const u8 TIMER_PRESCALE_64 = (1<<CS11) | (1<<CS10);
const u8 TIMER_PRESCALE_256 = (1<<CS12);
const u8 TIMER_PRESCALE_1024 = (1<<CS12) | (1<<CS10);

u16 _timeout;
void (*_timer1a_callback)(void);
void (*_timer1b_callback)(void);
void (*_timer1_overflow_callback)(void);

Timer1::Timer1()
{
	TIMSK = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	_timeout = 0;
	_timer1a_callback = 0;
	_timer1b_callback = 0;
	_timer1_overflow_callback = 0;
}

Timer1::~Timer1()
{
	TIMSK = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;

	_timer1a_callback = 0;
	_timer1b_callback = 0;
	_timer1_overflow_callback = 0;
}

ISR(TIMER1_OVF_vect)
{
	if (_timer1_overflow_callback != 0)
	{
		cli();
		_timer1_overflow_callback();
		sei();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (_timer1a_callback != 0)
	{
		cli();
		_timer1a_callback();
		//OCR1A = _timeout;
		//TCNT1 = 0;
		sei();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if (_timer1b_callback != 0)
	{
		cli();
		_timer1b_callback();
		//OCR1B = _timeout;
		//TCNT1 = 0;
		sei();
	}
}

void Timer1::setTimeOutACallback(u16 timeout, void (*callback)(void))
{
	//u8 mask = (1<<OCIE0)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<OCIE2);

	_timeout = timeout;
	_timer1a_callback = callback;

	TIMSK |= (1<<OCIE1A);
	OCR1A = _timeout;
}

void Timer1::setTimeOutBCallback(u16 timeout, void (*callback)(void))
{
	//u8 mask = (1<<OCIE0)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<OCIE2);

	_timeout = timeout;
	_timer1b_callback = callback;

	TIMSK |= (1<<OCIE1B);
	OCR1B = _timeout;
}

void Timer1::setOverFlowCallback(void (*callback)(void))
{
	//u8 mask = (1<<TOIE0) | (1<<TOIE1) | (1<<TOIE2);
	TIMSK |= (1<<TOIE1);

	_timer1_overflow_callback = callback;
}

//~ 0 : timer off
//~ 1 : precaler = 1
//~ 2 : prescaler = 8
//~ 3 : prescaler = 64
//~ 4 : prescaler = 256
//~ 5 : prescaler = 1024
void Timer1::setPrescaler(u8 freq)
{
	//TCCR1B = ICNC1	ICES1	–-----	WGM13	WGM12	CS12	CS11	CS10
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

	switch (freq)
	{
		case 0:
			TCCR1B |= TIMER_OFF;
			break;
		case 1:
			TCCR1B |= TIMER_PRESCALE_1;
			break;
		case 2:
			TCCR1B |= TIMER_PRESCALE_8;
			break;
		case 3:
			TCCR1B |= TIMER_PRESCALE_64;
			break;
		case 4:
			TCCR1B |= TIMER_PRESCALE_256;
			break;
		case 5:
			TCCR1B |= TIMER_PRESCALE_1024;
			break;
	}
}

void Timer1::ctcWaveForm()
{
//TCCR1A = COM1A1	COM1A0	COM1B1	COM1B0	FOC1A	FOC1B	WGM11	WGM10
//TCCR1B = ICNC1	ICES1	–-----	WGM13	WGM12	CS12	CS11	CS10
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~(1 << WGM13);
	TCCR1B |= (1 << WGM12);
}

//~ mode 0 : normal operation, OC0 disconnected
//~ mode 1 : Toggle OC0 on compare match
//~ mode 2 : clear OC0 on compare match
//~ mode 3 : set OC0 on compare match
void Timer1::setCompareOutputModeA(u8 mode)
{
//TCCR1A = COM1A1	COM1A0	COM1B1	COM1B0	FOC1A	FOC1B	WGM11	WGM10
//TCCR1B = ICNC1	ICES1	–-----	WGM13	WGM12	CS12	CS11	CS10
	TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));
	TCCR1A |= ((mode & 0x03) << COM1A0);
}

//~ mode 0 : normal operation, OC0 disconnected
//~ mode 1 : Toggle OC0 on compare match
//~ mode 2 : clear OC0 on compare match
//~ mode 3 : set OC0 on compare match
void Timer1::setCompareOutputModeB(u8 mode)
{
//TCCR1A = COM1A1	COM1A0	COM1B1	COM1B0	FOC1A	FOC1B	WGM11	WGM10
//TCCR1B = ICNC1	ICES1	–-----	WGM13	WGM12	CS12	CS11	CS10
	TCCR1A &= ~((1 << COM1B0) | (1 << COM1B1));
	TCCR1A |= ((mode & 0x03) << COM1B0);
}
