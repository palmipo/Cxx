#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>

#include "raspii2c.h"
#include "ada772.h"
#include "hd44780.h"
#include "mcp23017.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "pollfactory.h"

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

static int32_t irq(PollDevice *, void * user_data)
{
/*
	try
	{
		ADA772 * lcd_io = (ADA772 *)user_data;
		lcd_io->scrute();
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
	}
*/
	return 0;
}

int main(int argc, char **argv)
{
	int fd_irq = -1;

	if (argc < 3)
	{
		std::cout << argv[0] << " </dev/i2c-1 /dev/gpiochip0>" << std::endl;
		return -1;
	}

	try
	{
		RaspiI2C i2c(argv[1]);
		MCP23017 pia(0, &i2c);

		// virtual void init(u8 port, u8 dir=0, u8 pol=0, u8 pullup=0, u8 irq=0, u8 defval_pin=0, u8 defval=0);
		pia.init(0, 0x1F, 0x1F, 0x1F, 0x1F);
		pia.init(1, 0, 0, 0);

		ADA772 lcd_io(&pia);
		lcd_io.setBackLight(1);
		lcd_io.setButtonsCallback(bouton, 0);

		HD44780 lcd(&lcd_io, 16, 2);

		RaspiGpioFactory gpio_fact(argv[2]);
		RaspiGpio * gpio = gpio_fact.event(14, GPIOEVENT_REQUEST_FALLING_EDGE);

		PollFactory poll_fact;
		poll_fact.setActionInCallback(irq, &lcd_io);

		std::string str_date;
		struct tm *la_date;
		long t;
		int cpt = 0;
		while (cpt < 500)
		{
			time(&t);
			la_date = localtime(&t);
			std::stringstream buf_date;
			buf_date << std::setw(2) << std::setfill('0') << la_date->tm_mday << "-" << std::setw(2) << std::setfill('0') << 1 + la_date->tm_mon << "-" << std::setw(4) << std::setfill('0') << 1900 + la_date->tm_year << " " << std::setw(2) << std::setfill('0') << la_date->tm_hour <<":" << std::setw(2) << std::setfill('0') << la_date->tm_min;
			str_date = buf_date.str();
			
			lcd.setPosition(0, 0);
			lcd.setText((int8_t *)str_date.c_str(), str_date.length());

			lcd.setPosition(1, 0);
			lcd.setText((int8_t *)"20 C", 4);
			
			poll_fact.scrute(10);

			std::cout << "compteur : " << cpt << std::endl;
			++cpt;
		}
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	close(fd_irq);

	return 0;
}
