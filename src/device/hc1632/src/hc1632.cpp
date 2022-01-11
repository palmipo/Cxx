#include "hc1632.h"
#include "gpio.h"
#include "log.h"

#include <chrono>
#include <thread>

#define TEMPO 1

HC1632::HC1632(Gpio * data, Gpio * write, std::vector < Gpio * > cs)
: _gpio_data(data)
, _gpio_write(write)
, _gpio_chipSelect(cs)
{
	uint8_t valeur = 1;
	_gpio_write->write(valeur);
	_gpio_data->write(valeur);

	std::vector < Gpio * >::iterator it = cs.begin();
	while (it != cs.end())
	{
		// _gpio_chipSelect.push_back(*it);
		(*it)->write(valeur);
		it++;
	}
	
	init(cs.size());
}

void HC1632::write_chipselect(int32_t matrice, uint8_t valeur)
{
	uint8_t value = 1 - valeur;
	_gpio_chipSelect[matrice]->write(value);
	std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));
}


void HC1632::write_bit(uint8_t valeur)
{
	uint8_t value = 0;
	_gpio_write->write(value);

	value = valeur?1:0;
	_gpio_data->write(value);
	std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

	value = 1;
	_gpio_write->write(value);
	std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));
}


void HC1632::write_sys(int32_t matrice, uint8_t on)
{
  write_chipselect(matrice, 1);
  
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
  
  write_chipselect(matrice, 0);
}


void HC1632::write_com_option(int32_t matrice, uint8_t config)
{
  write_chipselect(matrice, 1);

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

  write_chipselect(matrice, 0);
}


void HC1632::write_mode(int32_t matrice, uint8_t mode)
{
  write_chipselect(matrice, 1);
  
  write_bit(1);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  write_bit(0);
  write_bit(0);
  write_bit(1);
  
  write_bit(mode & 0x02);
  write_bit(mode & 0x01);
  write_bit(0);
  write_bit(0);
  
  write_bit(0);
  
  write_chipselect(matrice, 0);
}


void HC1632::write_led(int32_t matrice, uint8_t on)
{
  write_chipselect(matrice, 1);
  
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
  
  write_chipselect(matrice, 0);
}


void HC1632::write_blink(int32_t matrice, uint8_t on)
{
  write_chipselect(matrice, 1);
  
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
  
  write_chipselect(matrice, 0);
}


void HC1632::write_led_pwm(int32_t matrice, uint8_t intensity)
{
  write_chipselect(matrice, 1);
  
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
  
  write_chipselect(matrice, 0);
}


void HC1632::write_led_buffer(int32_t matrice, uint8_t * buffer, int32_t length)
{
  write_chipselect(matrice, 1);
  
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

  write_chipselect(matrice, 0);
}


void HC1632::write_led_pixel(int32_t matrice, uint8_t quartet, uint8_t buffer)
{
	write_chipselect(matrice, 1);

	write_bit(1);
	write_bit(0);
	write_bit(1);

	/* address */
	for (int32_t i=0; i<7; ++i)
	{
		write_bit(quartet&(1<<(6-i)));
	}

	/* data */
	for (int32_t i=0; i<4; ++i)
	{
		write_bit(buffer&(1<<i));
	}

	write_chipselect(matrice, 0);
}

void HC1632::init(int32_t nb_matrix)
{
	for (int32_t i=0; i<nb_matrix; ++i)
	{
		// SYS DIS
		write_sys(i, 0x00);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

		// COM OPTION
		write_com_option(i, 1);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

		// MASTER MODE
		write_mode(i, (i==0) ? 2 : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

		// SYS ON
		write_sys(i, 0x01);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

		// LED ON
		write_led(i, 0x01);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

		write_blink(i, 0x00);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));

		write_led_pwm(i, 0x02);
		std::this_thread::sleep_for(std::chrono::microseconds(TEMPO));
	}
}
