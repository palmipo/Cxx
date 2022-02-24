#include <stdio.h>
#include "pico/stdlib.h"
#include "picoi2c.h"
#include "pcf8574at.h"
#include "lcd2004.h"
#include "hd44780.h"
#include "tempo.h"
#include <sstream>

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 100KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c_default
#define I2C_SDA PICO_DEFAULT_I2C_SDA_PIN
#define I2C_SCL PICO_DEFAULT_I2C_SCL_PIN

int main()
{
	stdio_init_all();

	PicoI2C i2c(I2C_PORT, I2C_SDA, I2C_SCL);

	PCF8574AT pia(0, &i2c);
	pia.setDirection(0, 0);

	LCD2004 lcd_io(&pia);
	lcd_io.setBackLight(1);
	
	HD44780 lcd(&lcd_io, 20, 4);

	int64_t i=0;
	while(1)
	{
		std::stringstream ss;
		ss << i;

		lcd.setPosition(1, 1);
		lcd.setText((int8_t*)ss.str().c_str(), ss.str().length());
		Tempo:: millisecondes (500);

		i++;
	}

	return 0;
}
