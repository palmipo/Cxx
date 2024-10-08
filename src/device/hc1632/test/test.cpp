#include "hc1632.h"
#include "raspigpioexception.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "raspipia.h"
#include "log.h"
#include "tempo.h"
#include "polldevice.h"
#include "pollfactory.h"
#include <cstdint>
#include <sstream>
#include <thread>
#include <iostream>
#include <cstring>
#include <vector>

uint8_t chiffre[10][48] ={
  { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
, { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00 }
};

int32_t NB_POINT = 48;
int32_t NB_MATRIX = 10;
int32_t DROITE_PIN = 23;
int32_t GAUCHE_PIN = 24;
int32_t FIN_PIN = 10; //9;
int32_t DATA_PIN = 7;
int32_t WRITE_PIN = 11;
int32_t CS_PIN[] = { 12, 13, 8, 17, 22, 5, 6, 25, 27, 18 };
int32_t compteur = 0;
static uint64_t last_pressed = 0;
static int32_t callback(PollDevice * device, void * user_data)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "callback");

        // GPIOEVENT_EVENT_RISING_EDGE
        // GPIOEVENT_EVENT_FALLING_EDGE
	uint32_t id;
	uint64_t time_pressed;
        int32_t res = ((RaspiGpio *)device)->readEvent(&id, &time_pressed);
	{
	std::stringstream ss;
	ss << "callback : device->readEvent() id=" << id << " time=" << time << " " << device->name() << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	uint64_t delta = time_pressed - last_pressed;
	{
	std::stringstream ss;
	ss << "delta : " << delta;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	if (delta > 20000)
	{
		last_pressed = time_pressed;

		std::vector<HC1632 *>* aff = ((std::vector<HC1632 *>*)user_data);
		std::vector<HC1632 *> afficheur = *aff;
		afficheur[0]->write_led_buffer(chiffre[compteur], NB_POINT);
		compteur += 1;
		compteur %= 10;
	}
	return res;
}

static void scrute(PollFactory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(100);
	}
}

int main(int argc, char **argv)
{
	try
	{
	RaspiGpioFactory gpio_factory("/dev/gpiochip0");

	RaspiGpio * data = gpio_factory.outputs(&DATA_PIN, 1);
	RaspiGpio * clk = gpio_factory.outputs(&WRITE_PIN, 1);

	RaspiPia pia_data(data);
	RaspiPia pia_clk(clk);

	std::vector<HC1632 *> afficheur;

	for (int32_t i=0; i<NB_MATRIX; ++i)
	{
		RaspiGpio * cs = gpio_factory.outputs(CS_PIN+i, 1);
		RaspiPia * pia_cs = new RaspiPia(cs);
		afficheur.push_back( new HC1632(&pia_data, &pia_clk, pia_cs, (i==0)) );
	}

		int32_t fin = 0;

		RaspiGpio * gpio_droite = gpio_factory.event(DROITE_PIN, GPIOEVENT_EVENT_FALLING_EDGE);
		RaspiGpio * gpio_gauche = gpio_factory.event(GAUCHE_PIN, GPIOEVENT_EVENT_FALLING_EDGE);
		RaspiGpio * gpio_fin = gpio_factory.event(FIN_PIN, GPIOEVENT_EVENT_FALLING_EDGE);

		PollFactory poll_factory;
		poll_factory.setActionInCallback(callback, &afficheur);
		poll_factory.add(gpio_gauche);
		poll_factory.add(gpio_droite);
		poll_factory.add(gpio_fin);

		std::thread t(scrute, &poll_factory, &fin);

		Tempo::minutes(1);
		//Tempo::minutes(10);

		fin = 1;
		t.join();

		Tempo::minutes(1);

		for (int32_t i=0; i<NB_MATRIX; ++i)
		{
			delete afficheur[i];
		}

		std::cout << "fin" << std::endl;

		return 0;
	}
	catch (RaspiGpioException e)
	{
		std::cerr << "exception !!!" << e.what() << std::endl;
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}
	catch (...)
	{
		std::cerr << "exception !!!" << std::endl;
	}
}

