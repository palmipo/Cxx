#include "raspii2c.h"
#include "pcf8574at.h"
#include "lcd2004.h"
#include "hd44780.h"
#include "tempo.h"
#include <sstream>
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	try
	{
		RaspiI2C i2c("/dev/i2c-1");

//		DS1621 tempe(0, &i2c);
//		tempe.debut_conversion();

		PCF8574AT pia(0, &i2c);

		LCD2004 lcd_io(&pia);
		lcd_io.setBackLight(1);
		
		HD44780 lcd(&lcd_io, 4, 20);

		std::string str_date, str_heure, str_tempe;
		struct tm *la_date;
		long t;
		while (1)
		{
			time(&t);
			la_date = localtime(&t);
			std::stringstream buf1;
			buf1 << std::setw(2) << std::setfill('0') << la_date->tm_mday << "/" << std::setw(2) << std::setfill('0') << 1 + la_date->tm_mon << "/" << std::setw(4) << std::setfill('0') << 1900 + la_date->tm_year;
			str_date = buf1.str();

			std::stringstream buf2;
			buf2 << std::setw(2) << std::setfill('0') << la_date->tm_hour << ":" << std::setw(2) << std::setfill('0') << la_date->tm_min << ":" << std::setw(2) << std::setfill('0') << la_date->tm_sec;
			str_heure = buf2.str();

			std::stringstream buf3;
			buf3 << str_heure.length();
			str_tempe = buf3.str();
			
			//afficheur.returnHome();
			lcd.setPosition(0, 0);
			lcd.setText((int8_t*)str_date.c_str(), str_date.length());

			lcd.setPosition(0, 12);
			lcd.setText((int8_t*)str_heure.c_str(), str_heure.length());

//			std::stringstream buf3;
//			buf3 << std::setw(2) << std::setfill('0') << (int)tempe.lecture_temperature() << " C";
//			str_tempe = buf3.str();
			
//			lcd.setPosition(3, 1);
//			lcd.setText((int8_t*)str_tempe.c_str(), str_tempe.length());
	
			Tempo::millisecondes(500);
		}

		lcd_io.setBackLight(0);

	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}
