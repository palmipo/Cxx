#include "rs232.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void (*_rs232_callback)(unsigned char);

RS232::RS232()
{
	UCSRA=0x00;
	UCSRB=0x00;
	UCSRC=0x00;
	UBRRH=0x00;
	UBRRL=0x00;

	_rs232_callback = 0;
}

RS232::~RS232()
{
	UCSRB = 0;

	_rs232_callback = 0;
}


void RS232::init(unsigned short baud, unsigned char parity, unsigned char n_bit, unsigned char n_stop)
{
	_rs232_callback = 0;

	unsigned char BAUD_PRESCALE = F_CPU / 16 / baud - 1;

	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;
	
	// emission / reception / interruption reception
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);

	unsigned char ctrl = (1 << URSEL);
	
	// parite
	switch (parity)
	{
		case 'E':
			ctrl |= (1 << UPM1);
		break;
		case 'O':
			ctrl |= (1 << UPM1) | (1 << UPM0);
		break;
	}
	
	// stop bit
	switch (n_stop)
	{
		case 2:
			ctrl |= (1 << USBS);
		break;
	}

	switch (n_bit)
	{
		//case 5:
			//ctrl |= 0;
		//break;
		case 6:
			ctrl |= (1 << UCSZ0);
		break;
		case 7:
			ctrl |= (1 << UCSZ1);
		break;
		case 8:
			ctrl |= (1 << UCSZ0) | (1 << UCSZ1);
		break;
		case 9:
			ctrl |= (1 << UCSZ0) | (1 << UCSZ1) | (1 << UCSZ2);
		break;
	}

	UCSRC = ctrl;
}

ISR(USART_RXC_vect)
{
	if (_rs232_callback != 0)
	{
		cli();
		_rs232_callback(UDR);
		sei();
	}
}

void RS232::send(unsigned char * octets, unsigned char length)
{
	cli();
	unsigned char i;
	for (i=0; i<length; i++)
	{
		while(!(UCSRA & (1 << UDRIE)));
		UDR = octets[i];
	}
	sei();
}

void RS232::recv(unsigned char * octets, unsigned char length)
{
	cli();
	unsigned char i;
	for (i=0; i<length; i++)
	{
		octets[i] = UDR;
		while(!(UCSRA & (1 << UDRIE)));
	}
	sei();
}

void RS232::setRecvCallback(void (*callback)(unsigned char))
{
	_rs232_callback = callback;
}
