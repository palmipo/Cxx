#include "hc1632.h"
#include "pia.h"
#include "tempo.h"
#include "log.h"

int32_t TEMPO = 100;
int32_t TEMPO_1_2 = 50;

HC1632::HC1632(PIA * data, PIA * write, PIA * cs, uint8_t master_mode)
: _gpio_data(data)
, _gpio_write(write)
, _gpio_chipSelect(cs)
{
	_gpio_write->write(1);
	_gpio_data->write(1);
	_gpio_chipSelect->write(1);

	init(master_mode);
}

void HC1632::write_chipselect(uint8_t valeur)
{
	_gpio_chipSelect->write(valeur?0:1);
	Tempo::microsecondes(TEMPO);
}


void HC1632::write_bit(uint8_t valeur)
{
	_gpio_write->write(0);
	Tempo::microsecondes(TEMPO_1_2);

	_gpio_data->write(valeur?1:0);
	Tempo::microsecondes(TEMPO_1_2);

	_gpio_write->write(1);
	Tempo::microsecondes(TEMPO);
}


void HC1632::write_sys(uint8_t on)
{
  write_chipselect(1);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(on);
  
  write_bit(0);
  
  write_chipselect(0);
}


void HC1632::write_com_option(uint8_t config)
{
  write_chipselect(1);

  write_bit(1);
  write_bit(0);
  write_bit(0);

  write_bit(0);
  write_bit(0);
  write_bit(1);
  write_bit(0);

  write_bit(config & 0x02); // a
  write_bit(config & 0x01); // b
  write_bit(0);
  write_bit(0);

  write_bit(0);

  write_chipselect(0);
}


void HC1632::write_mode(uint8_t mode)
{
  write_chipselect(1);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(1);
  
  write_bit(mode);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  
  write_chipselect(0);
}


void HC1632::write_led(uint8_t on)
{
  write_chipselect(1);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(1);
  write_bit(on);
  
  write_bit(0);
  
  write_chipselect(0);
}


void HC1632::write_blink(uint8_t on)
{
  write_chipselect(1);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  write_bit(on);
  
  write_bit(0);
  
  write_chipselect(0);
}


void HC1632::write_led_pwm(uint8_t intensity)
{
  write_chipselect(1);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  
  write_bit(1);
  write_bit(0);
  write_bit(1);
  write_bit(0);
  
  write_bit(intensity & 0x08);
  write_bit(intensity & 0x04);
  write_bit(intensity & 0x02);
  write_bit(intensity & 0x01);
  
  write_bit(0);
  
  write_chipselect(0);
}


void HC1632::write_led_buffer(uint8_t * buffer, int32_t length)
{
  write_chipselect(1);
  
  write_bit(1);
  write_bit(0);
  write_bit(1);
  
  /* address */
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(0);

  /* data */
  for (int32_t j=0; j<length; ++j)
  {
    for (int32_t i=0; i<8; ++i)
    {
      write_bit(buffer[j] & (1<<i));
    }
  }

  write_chipselect(0);
}


void HC1632::write_led_pixel(uint8_t quartet, uint8_t buffer)
{
	write_chipselect(1);

	write_bit(1);
	write_bit(0);
	write_bit(1);

	/* address */
	for (int32_t i=0; i<7; ++i)
	{
		write_bit(quartet & (1<<(6-i)));
	}

	/* data */
	for (int32_t i=0; i<4; ++i)
	{
		write_bit(buffer & (1<<i));
	}

	write_chipselect(0);
}

void HC1632::init(uint8_t master_mode)
{
	// SYS DIS
	write_sys(0);
	Tempo::microsecondes(TEMPO);

	// COM OPTION
	write_com_option(1);
	Tempo::microsecondes(TEMPO);

	// MASTER MODE
	write_mode(master_mode);
	Tempo::microsecondes(TEMPO);

	// SYS ON
	write_sys(1);
	Tempo::microsecondes(TEMPO);

	// LED ON
	write_led(1);
	Tempo::microsecondes(TEMPO);

	write_blink(0);
	Tempo::microsecondes(TEMPO);

	write_led_pwm(0x0F);
	Tempo::microsecondes(TEMPO);
}
