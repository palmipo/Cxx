/*
 * ws2812b.cpp
 *
 * Created: 22/10/2019 00:02:39
 * Author : toff
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include "ws2812b.h"


void france(uint8_t voie, uint8_t offset, uint8_t intensite, uint8_t * pixels)
{
	setPixel(voie, offset + 0, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 1, 0, 0, intensite, pixels);
	setPixel(voie, offset + 2, 0, 0, intensite, pixels);
	setPixel(voie, offset + 3, 0, 0, intensite, pixels);
	setPixel(voie, offset + 4, 0, 0, intensite, pixels);
	setPixel(voie, offset + 5, 0, 0, intensite, pixels);
	setPixel(voie, offset + 6, 0, 0, intensite, pixels);
	setPixel(voie, offset + 7, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 8, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 9, intensite, 0, 0, pixels);
	setPixel(voie, offset + 10, intensite, 0, 0, pixels);
	setPixel(voie, offset + 11, intensite, 0, 0, pixels);
	setPixel(voie, offset + 12, intensite, 0, 0, pixels);
	setPixel(voie, offset + 13, intensite, 0, 0, pixels);
	setPixel(voie, offset + 14, intensite, 0, 0, pixels);
	setPixel(voie, offset + 15, intensite, intensite, intensite, pixels);
}

void angleterre(uint8_t voie, uint8_t offset, uint8_t intensite, uint8_t * pixels)
{
	setPixel(voie, offset + 0, intensite, 0, 0, pixels);
	setPixel(voie, offset + 1, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 2, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 3, intensite, 0, 0, pixels);
	setPixel(voie, offset + 4, intensite, 0, 0, pixels);
	setPixel(voie, offset + 5, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 6, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 7, intensite, 0, 0, pixels);
	setPixel(voie, offset + 8, intensite, 0, 0, pixels);
	setPixel(voie, offset + 9, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 10, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 11, intensite, 0, 0, pixels);
	setPixel(voie, offset + 12, intensite, 0, 0, pixels);
	setPixel(voie, offset + 13, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 14, intensite, intensite, intensite, pixels);
	setPixel(voie, offset + 15, intensite, 0, 0, pixels);
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;

	uint8_t pixels[NB_LED*NB_BIT];
	memset(pixels, 0, NB_LED*NB_BIT);

	while(1)
	{
		//memset(pixels, 0, NB_LED*NB_BIT);
		france(0, 0, 2, pixels);
		angleterre(0, 16, 2, pixels);

		affiche(pixels);
		_delay_ms(1000);
	}
}

