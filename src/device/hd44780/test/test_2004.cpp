#ifdef USB_I2C
#include "rs232.h"
#include "rs232factory.h"
#include "usb_i2c.h"
#else
#include "raspii2c.h"
#endif
#include "mcp23017.h"
#include "lcd2004.h"
#include "hd44780.h"
#include <poll.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " </dev/i2c-1>" << std::endl;
		return -1;
	}

	try
	{
#ifdef USB_I2C
		RS232Factory factory;
		RS232 * serial = factory.addSerialConnection(argv[1]);
		UsbI2C i2c(serial);
#else
		RaspiI2C i2c(argv[1]);
#endif

//		DS1621 tempe(0, &i2c);
//		tempe.debut_conversion();

		lcd2004 lcd(&i2c);
		lcd.setBackLight(1);

		std::string str_date, str_heure, str_tempe;
		struct tm *la_date;
		long t;
		while (1)
		{
			time(&t);
			la_date = localtime(&t);
			std::stringstream buf1;
			buf1 << std::setw(2) << std::setfill('0') << la_date->tm_mday << "-" << std::setw(2) << std::setfill('0') << 1 + la_date->tm_mon << "-" << std::setw(4) << std::setfill('0') << 1900 + la_date->tm_year;
			str_date = buf1.str();

			std::stringstream buf2;
			buf2 << std::setw(2) << std::setfill('0') << la_date->tm_hour << ":" << std::setw(2) << std::setfill('0') << la_date->tm_min << ":" << std::setw(2) << std::setfill('0') << la_date->tm_sec;
			str_heure = buf2.str();
			
			//afficheur.returnHome();
			lcd.lcd()->setPosition(1, 1);
			lcd.lcd()->setText((s8*)str_date.c_str(), str_date.length());

			lcd.lcd()->setPosition(2, 1);
			lcd.lcd()->setText((s8*)str_heure.c_str(), str_heure.length());

//			std::stringstream buf3;
//			buf3 << std::setw(2) << std::setfill('0') << (int)tempe.lecture_temperature() << " C";
//			str_tempe = buf3.str();
			
//			lcd.lcd()->setPosition(3, 1);
//			lcd.lcd()->setText((s8*)str_tempe.c_str(), str_tempe.length());
	
			poll(0, 0, 1000);
		}

		lcd.setBackLight(0);

	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}
