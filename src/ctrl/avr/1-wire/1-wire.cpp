#include "1-wire.h"
#include "timer0.h"
#include "batratypes.h"

Timer0 oneWireTimer;
u8 oneWireAutomate;
u8 oneWireCpt;

// time out toutes les 1µs
void oneWire_callback()
{
	if ((oneWireAutomate == 0) && (oneWireCpt == 60))
	{
		oneWireAutomate = 1;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 1) && (oneWireCpt == 60))
	{
		oneWireAutomate = 2;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 2) && (oneWireCpt == 60))
	{
		oneWireAutomate = 3;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 3) && (oneWireCpt == 60))
	{
		oneWireAutomate = 4;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 4) && (oneWireCpt == 60))
	{
		oneWireAutomate = 5;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 5) && (oneWireCpt == 60))
	{
		oneWireAutomate = 6;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 6) && (oneWireCpt == 60))
	{
		oneWireAutomate = 7;
		oneWireCpt = 0;
	}
	else if ((oneWireAutomate == 7) && (oneWireCpt == 60))
	{
		oneWireAutomate = 8;
		oneWireCpt = 0;
		PORTD = 0xFF;
	}
	else if ((oneWireAutomate == 8) && (oneWireCpt == 15))
	{
		oneWireAutomate = 9;
		oneWireCpt = 0;
		DDRD = 0xFF;
		PORTD = 0xFF;
	}
	else if ((oneWireAutomate == 9) && (oneWireCpt < 75))
	{
		if (PIND2 == 0)
		{
			oneWireAutomate = 10;
			oneWireCpt = 0;
			DDRD = 0xFF;
			PORTD = 0xFF;
		}
	}
}

oneWire::oneWire()
{
	oneWireTimer.ctcWaveForm();
	oneWireTimer.setCompareValue(8);
	oneWireTimer.setPrescaler(0);
	oneWireTimer.setTimeOutCallback(oneWire_callback);

	DDRD = 0xFF;
	PORTD = 0xFF;
}
oneWire::~oneWire()
{}

void oneWire::reset()
{
	DDRD = 0xFF;
	PORTD = 0;
	oneWireAutomate = 0;
	oneWireCpt = 0;
	oneWireTimer.setPrescaler(1);
}

void oneWire::send_bit()
{
	
}

void oneWire::recv_bit()
{
	
}
