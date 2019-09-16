#include "externalint.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void (*_int0_callback)();
void (*_int1_callback)();
void (*_int2_callback)();

ExternalInt::ExternalInt()
{
	_int0_callback = 0;
	_int1_callback = 0;
	_int2_callback = 0;

	MCUCR  &= ~((1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00));
	MCUCSR &= ~(1<<ISC2);
	GICR   &= ~((1<<INT0) | (1<<INT1) | (1<<INT2));
}

ExternalInt::~ExternalInt()
{
	_int0_callback = 0;
	_int1_callback = 0;
	_int2_callback = 0;

	MCUCR  &= ~((1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00));
	MCUCSR &= ~(1<<ISC2);
	GICR   &= ~((1<<INT0) | (1<<INT1) | (1<<INT2));
}

void ExternalInt::unset_irq0()
{
	_int0_callback = 0;

	MCUCR  &= ~((1<<ISC01) | (1<<ISC00));
	GICR   &= ~(1<<INT0);
}

void ExternalInt::set_irq0(unsigned char irq, void (*callback)())
{
	unsigned char mask1 = MCUCR & ~((1<<ISC01) | (1<<ISC00));
	unsigned char mask3 = GICR & ~(1<<INT0);
	
	unsigned char i1 =  irq & 1;
	unsigned char i2 = (irq & 2) >> 1;
	MCUCR = mask1 | (i2<<ISC01) | (i1<<ISC00);
	GICR  = mask3 | (1<<INT0);
	_int0_callback = callback;
}

void ExternalInt::unset_irq1()
{
	_int1_callback = 0;

	MCUCR  &= ~((1<<ISC11) | (1<<ISC10));
	GICR   &= ~(1<<INT1);
}

void ExternalInt::set_irq1(unsigned char irq, void (*callback)())
{
	unsigned char mask1 = MCUCR & ~((1<<ISC11) | (1<<ISC10));
	unsigned char mask3 = GICR & ~(1<<INT1);
	
	unsigned char i1 =  irq & 1;
	unsigned char i2 = (irq & 2) >> 1;
	MCUCR = mask1 | (i2<<ISC11) | (i1<<ISC10);
	GICR  = mask3 | (1<<INT1);
	_int1_callback = callback;
}

void ExternalInt::unset_irq2()
{
	_int2_callback = 0;

	MCUCSR &= ~(1<<ISC2);
	GICR   &= ~(1<<INT2);
}

void ExternalInt::set_irq2(unsigned char irq, void (*callback)())
{
	unsigned char mask2 = MCUCSR & ~(1<<ISC2);
	unsigned char mask3 = GICR & ~(1<<INT2);
	unsigned char i = irq & 1;
	MCUCSR = mask2 | (i<<ISC2);
	GICR   = mask3 | (i<<INT2);
	_int2_callback = callback;
}

ISR(INT0_vect)
{
	if (_int0_callback != 0)
	{
		cli();
		_int0_callback();
		sei();
	}
}

ISR(INT1_vect)
{
	if (_int1_callback != 0)
	{
		cli();
		_int1_callback();
		sei();
	}
}

ISR(INT2_vect)
{
	if (_int2_callback != 0)
	{
		cli();
		_int2_callback();
		sei();
	}
}
