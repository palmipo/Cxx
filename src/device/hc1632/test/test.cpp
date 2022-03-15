#include "hc1632.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "raspipia.h"
#include <iostream>
#include <cstring>

uint8_t chiffre[10][48] ={
  { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
};

int32_t NB_POINT = 48;
int32_t NB_MATRIX = 10;
int32_t DROITE_PIN = 23;
int32_t RAZ_PIN = 10;
int32_t GAUCHE_PIN = 24;
int32_t FIN_PIN = 9;
int32_t DATA_PIN = 7;
int32_t WRITE_PIN = 11;
int32_t CS_PIN[] = { 25, 8, 12, 27, 13, 6, 17, 5, 22, 18 };

int main(int argc, char **argv)
{
	try
	{
	RaspiGpioFactory gpio_fact("/dev/gpiochip0");

	RaspiGpio * data = gpio_fact.outputs(&DATA_PIN, 1);
	RaspiGpio * clk = gpio_fact.outputs(&WRITE_PIN, 1);
	RaspiGpio * cs = gpio_fact.outputs(CS_PIN, 1);

	std::cout << "pia" << std::endl;

	RaspiPia pia_data(data);
	RaspiPia pia_clk(clk);
	RaspiPia pia_cs(cs);

	std::cout << "afficheur" << std::endl;

	HC1632 afficheur(&pia_data, &pia_clk, &pia_cs, 1);
	std::cout << "write led buffer" << std::endl;

	uint8_t buf[NB_POINT];
	std::memset(buf, 0xFF, NB_POINT);
	afficheur.write_led_buffer(buf, NB_POINT);

	std::cout << "fin" << std::endl;

	return 0;
	}
	catch (...)
	{
		std::cerr << "exception !!!" << std::endl;
	}
}

