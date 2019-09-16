#ifndef HC1632_H
#define HC1632_H

#include <cstdint>
#include <vector>

class Gpio;
class HC1632
{
	public:
		HC1632(Gpio * data, Gpio * write, std::vector < Gpio * > cs);

		void write_sys(int32_t matrice, uint8_t on);
		void write_com_option(int32_t matrice, uint8_t config);
		void write_mode(int32_t matrice, uint8_t mode);
		void write_led(int32_t matrice, uint8_t on);
		void write_blink(int32_t matrice, uint8_t on);
		void write_led_pwm(int32_t matrice, uint8_t intensity);
		void write_led_buffer(int32_t matrice, uint8_t * buffer, int32_t length);
		void write_led_pixel(int32_t matrice, uint8_t quartet, uint8_t buffer);

	protected:
		void init(int32_t nb_matrix);
		void write_chipselect(int32_t matrice, uint8_t valeur);
		void write_bit(uint8_t valeur);

		Gpio * _gpio_data;
		Gpio * _gpio_write;
		std::vector < Gpio * > _gpio_chipSelect;
};

#endif /* HC1632_H */