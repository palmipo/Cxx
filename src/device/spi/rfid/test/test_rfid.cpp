#include "raspispi.h"
#include "raspigpiofactory.h"
#include "raspigpioexception.h"
#include "raspigpio.h"
#include "raspipia.h"
#include "polldevice.h"
#include "pollexception.h"
#include "spiexception.h"
#include "mfrc522.h"
#include <cstdint>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	try
	{
		RaspiSPI spi("/dev/spidev0.0");
		spi.setMode(0);
		spi.setClockRate(1000000);
		spi.setBitPerWord(8);

		RaspiGpioFactory gpio_factory("/dev/gpiochip1");
		
		int32_t irq_pin = 24, rst_pin = 25;
		RaspiGpio * rst = gpio_factory.outputs(&rst_pin, 1);
		RaspiGpio * irq = gpio_factory.event(irq_pin, GPIOEVENT_REQUEST_FALLING_EDGE);

		RaspiPia rst_pia(rst);
		RaspiPia irq_pia(irq);

		MFRC522 rfid(&spi, &irq_pia, &rst_pia);

		rfid.init();

		uint8_t a, b;
		rfid.versionReg(&a, &b);

		std::stringstream ss;
		ss << "version : " << (int)a << ", " << (int)b;
		std::cout << ss.str() << std::endl;
	}
	catch (RaspiGpioException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (SPIException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (PollException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "erreur" << std::endl;
	}

	return 0;
}
