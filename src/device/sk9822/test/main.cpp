#include "sk9822.h"
#include "sk9822_gpio.h"
#include <cstdint>

int main(int argc, char ** argv)
{
	SK9822_gpio gpio("/dev/gpiochip0", 17, 18);
	SK9822 led((SK9822_io*)&gpio);
	
	uint32_t data[2];
	data[0] = 0xFFFFFF;
	data[1] = 0xFFFFFF;
	led.write(data, 2);

	return 0;
}
