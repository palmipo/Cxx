/*
 * toto.cpp
 *
 * Created: 19/01/2019 16:37:28
 * Author : toff
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

#define NB_LED	32
#define NB_BIT	24

// Generated by delay loop calculator
// at http://www.bretmulvey.com/avrdelay.html
// Delay 1 cycles
// 125 ns at 8.0 MHz
// 20 inst. clocks per bit: HHHHHxxxxxxxxLLLLLLL

void affiche(uint8_t *pixels)
{
	volatile uint8_t *ptr = pixels;
	volatile uint8_t b = *ptr++;
	cli();

	asm (
	"        ldi  r19, 0xFF"		"\n\t"
	"        ldi  r20, 0"			"\n\t"

	"        out %[port], r20"		"\n\t"
	"        ldi  r18, 256"			"\n\t"
	"RAZ:    dec  r18"				"\n\t"
	"        brne RAZ"				"\n\t"

	"		ldi  r17, %[nbled]"		"\n\t"
	"led:	ldi  r16, %[nbbit]"		"\n\t"

	"loop:	out %[port], r19"		"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"

	"       out %[port], %[byte]"	"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"

	"       out %[port], r20"		"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"
	"       nop"					"\n\t"

    "		ld   %[byte] , %a[ptr]+""\n\t"
	"       dec  r16"				"\n\t"
	"       brne loop"				"\n\t"
	"       dec  r17"				"\n\t"
	"       brne led"				"\n\t"
	: [byte] "+r" (b)
	: [port] "I" (_SFR_IO_ADDR(PORTB))
	, [ptr] "e" (ptr)
	, [nbled] "M" (NB_LED)
	, [nbbit] "M" (NB_BIT)
	);
	
	sei();
}

void setPixel(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t *pixels)
{
	int8_t i;
	for (i=0; i<8; ++i)
	{
		pixels[(NB_BIT * index) + i] = (green >> (7-i)) & 0x01;
		pixels[(NB_BIT * index) + i + 8] = (red >> (7-i)) & 0x01;
		pixels[(NB_BIT * index) + i + 16] = (blue >> (7-i)) & 0x01;
	}
}

void france(uint8_t offset, uint8_t intensite, uint8_t * pixels)
{
	setPixel(offset + 0, intensite, intensite, intensite, pixels);
	setPixel(offset + 1, 0, 0, intensite, pixels);
	setPixel(offset + 2, 0, 0, intensite, pixels);
	setPixel(offset + 3, 0, 0, intensite, pixels);
	setPixel(offset + 4, 0, 0, intensite, pixels);
	setPixel(offset + 5, 0, 0, intensite, pixels);
	setPixel(offset + 6, 0, 0, intensite, pixels);
	setPixel(offset + 7, intensite, intensite, intensite, pixels);
	setPixel(offset + 8, intensite, intensite, intensite, pixels);
	setPixel(offset + 9, intensite, 0, 0, pixels);
	setPixel(offset + 10, intensite, 0, 0, pixels);
	setPixel(offset + 11, intensite, 0, 0, pixels);
	setPixel(offset + 12, intensite, 0, 0, pixels);
	setPixel(offset + 13, intensite, 0, 0, pixels);
	setPixel(offset + 14, intensite, 0, 0, pixels);
	setPixel(offset + 15, intensite, intensite, intensite, pixels);
}

void angleterre(uint8_t offset, uint8_t intensite, uint8_t * pixels)
{
	setPixel(offset + 0, intensite, 0, 0, pixels);
	setPixel(offset + 1, intensite, intensite, intensite, pixels);
	setPixel(offset + 2, intensite, intensite, intensite, pixels);
	setPixel(offset + 3, intensite, 0, 0, pixels);
	setPixel(offset + 4, intensite, 0, 0, pixels);
	setPixel(offset + 5, intensite, intensite, intensite, pixels);
	setPixel(offset + 6, intensite, intensite, intensite, pixels);
	setPixel(offset + 7, intensite, 0, 0, pixels);
	setPixel(offset + 8, intensite, 0, 0, pixels);
	setPixel(offset + 9, intensite, intensite, intensite, pixels);
	setPixel(offset + 10, intensite, intensite, intensite, pixels);
	setPixel(offset + 11, intensite, 0, 0, pixels);
	setPixel(offset + 12, intensite, 0, 0, pixels);
	setPixel(offset + 13, intensite, intensite, intensite, pixels);
	setPixel(offset + 14, intensite, intensite, intensite, pixels);
	setPixel(offset + 15, intensite, 0, 0, pixels);
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;

	//uint8_t buffer[9*NB_BIT];
	uint8_t pixels[NB_LED*NB_BIT];
	memset(pixels, 0, NB_LED*NB_BIT);

	while(1)
	{
		france(0, 2, pixels);
		angleterre(16, 2, pixels);
		//angleterre(32, 5, pixels);
		//france(48, 5, pixels);

		affiche(pixels);
		_delay_ms(1000);
	}
	
	//setPixel(0, 0x80, 0x80, 0x80, buffer);
	//setPixel(1, 0x40, 0x40, 0x40, buffer);
	//setPixel(2, 0x20, 0x20, 0x20, buffer);
	//setPixel(3, 0x10, 0x10, 0x10, buffer);
	//setPixel(4, 0x8, 0x8, 0x8, buffer);
	//setPixel(5, 0x4, 0x4, 0x4, buffer);
	//setPixel(6, 0x2, 0x2, 0x2, buffer);
	//setPixel(7, 0x1, 0x1, 0x1, buffer);
	//setPixel(8, 0, 0, 0, buffer);

	//uint8_t i=6, j=0;
	//while(1)
	//{
		////for (i=0; i<9; i++)
		//{
			//memcpy(pixels + (((i+j) % NB_LED) * NB_BIT), buffer + (i * NB_BIT), NB_BIT);
		//}
		//affiche(pixels);
		//j = (j + 1) % NB_LED;
		//_delay_ms(1000);
	//}
}
