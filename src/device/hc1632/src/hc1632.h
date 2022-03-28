#ifndef HC1632_H
#define HC1632_H

#include <cstdint>

class CtrlPia;
class HC1632
{
	public:
		HC1632(CtrlPia * data, CtrlPia * write, CtrlPia * cs, uint8_t master_mode);
		virtual ~HC1632();

		virtual void write_sys(uint8_t on);
		virtual void write_com_option(uint8_t config);
		virtual void write_mode(uint8_t mode);
		virtual void write_led(uint8_t on);
		virtual void write_blink(uint8_t on);
		virtual void write_led_pwm(uint8_t intensity);
		virtual void write_led_buffer(uint8_t * buffer, int32_t length);
		virtual void write_led_pixel(uint8_t quartet, uint8_t buffer);

	protected:
		virtual void init(uint8_t master_mode);
		virtual void write_chipselect(uint8_t valeur);
		virtual void write_bit(uint8_t valeur);

	protected:
		CtrlPia * _gpio_data;
		CtrlPia * _gpio_write;
		CtrlPia * _gpio_chipSelect;
};

#endif /* HC1632_H */
