#ifndef HC1632_H
#define HC1632_H

#include <cstdint>

class PIA;
class HC1632
{
	public:
		HC1632(PIA * data, PIA * write, PIA * cs, uint8_t master_mode);

		void write_sys(uint8_t on);
		void write_com_option(uint8_t config);
		void write_mode(uint8_t mode);
		void write_led(uint8_t on);
		void write_blink(uint8_t on);
		void write_led_pwm(uint8_t intensity);
		void write_led_buffer(uint8_t * buffer, int32_t length);
		void write_led_pixel(uint8_t quartet, uint8_t buffer);

	protected:
		void init(uint8_t master_mode);
		void write_chipselect(uint8_t valeur);
		void write_bit(uint8_t valeur);

		PIA * _gpio_data;
		PIA * _gpio_write;
		PIA * _gpio_chipSelect;
};

#endif /* HC1632_H */
