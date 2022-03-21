#include "raspii2c.h"
#include "i2cexception.h"
#include "ada772.h"
#include "hd44780.h"
#include "mcp23017.h"
#include "raspigpioexception.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "pollfactory.h"
#include "polldevice.h"
#include "tempo.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <thread>

static void bouton(unsigned char value, void *user_data)
{
	try
	{
		std::cout << "bouton = " << (int)value << std::endl;
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
	}
}

static int32_t irq(PollDevice * gpio, void * user_data)
{
	std::cout << "irq leve !!!!" << std::endl;
	try
	{
		uint32_t id;
		uint64_t heure;
		((RaspiGpio *)gpio)->readEvent(&id, &heure);
		std::cout << "reception de " << id << " timestamp:" << heure << std::endl;

		/*
		ADA772 * lcd_io = (ADA772 *)user_data;
		lcd_io->scrute();
		*/
		/*
		HD44780 * lcd = (HD44780 *)user_data;

		std::string str_date;
		struct tm *la_date;
		long t;
		time(&t);
		la_date = localtime(&t);
		std::stringstream buf_date;
		buf_date << std::setw(2) << std::setfill('0') << la_date->tm_mday << "-" << std::setw(2) << std::setfill('0') << 1 + la_date->tm_mon << "-" << std::setw(4) << std::setfill('0') << 1900 + la_date->tm_year << " " << std::setw(2) << std::setfill('0') << la_date->tm_hour <<":" << std::setw(2) << std::setfill('0') << la_date->tm_min;

		str_date = buf_date.str();

		lcd->setPosition(0, 0);
		lcd->setText((int8_t *)str_date.c_str(), str_date.length());

		lcd->setPosition(1, 0);
		lcd->setText((int8_t *)"40 C", 4);
		*/
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
	}

	return 0;
}


static void scrute(PollFactory * fact, int32_t * fin)
{
	while (! *fin)
	{
		fact->scrute(100);
	}
}


int main(int argc, char **argv)
{
		RaspiI2C i2c("/dev/i2c-1");
		MCP23017 pia(0, &i2c);

		pia.init(0, 0x1F, 0x1F, 0x1F, 0x1F);
		pia.init(1, 0, 0, 0);

		ADA772 lcd_io(&pia);
		lcd_io.setBackLight(1);
		lcd_io.setButtonsCallback(bouton, 0);

		HD44780 lcd(&lcd_io, 2, 16);
		std::string str_date;
		struct tm *la_date;
		long t;
		time(&t);
		la_date = localtime(&t);
		std::stringstream buf_date;
		buf_date << std::setw(2) << std::setfill('0') << la_date->tm_mday << "-" << std::setw(2) << std::setfill('0') << 1 + la_date->tm_mon << "-" << std::setw(4) << std::setfill('0') << 1900 + la_date->tm_year << " " << std::setw(2) << std::setfill('0') << la_date->tm_hour <<":" << std::setw(2) << std::setfill('0') << la_date->tm_min;

		str_date = buf_date.str();

		lcd.setPosition(0, 0);
		lcd.setText((int8_t *)str_date.c_str(), str_date.length());

		lcd.setPosition(1, 0);
		lcd.setText((int8_t *)"20 C", 4);

		RaspiGpioFactory gpio_fact("/dev/gpiochip0");
		RaspiGpio * gpio = gpio_fact.event(4); //, GPIOEVENT_REQUEST_RISING_EDGE);

		PollFactory poll_fact;
		poll_fact.setActionInCallback(irq, &lcd);
		//poll_fact.setActionInCallback(irq, &lcd_io);
		poll_fact.add(gpio);

		int32_t fin = 0;

		std::thread my_thread(scrute, &poll_fact, &fin);
		my_thread.detach();

	try
	{
		Tempo::minutes(1);
		//Tempo::minutes(10);

	}
	catch(I2CException e)
	{
		std::cout << "erreur " << e.what() << std::endl;
		return -1;
	}
	catch(RaspiGpioException e)
	{
		std::cout << "erreur " << e.what() << std::endl;
		return -1;
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}
		fin = 1;
		//my_thread.join();

		Tempo::minutes(1);
		lcd_io.setBackLight(0);

	return 0;
}
