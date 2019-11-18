#ifndef BATMINTON_FACTORY_H
#define BATMINTON_FACTORY_H

#include "gpiofactory.h"
#include <termios.h>
#include <string>
#include <chrono>

const int32_t NB_MATRIX = 10;
const int32_t DROITE_PIN = 23;
const int32_t RAZ_PIN = 10;
const int32_t GAUCHE_PIN = 24;
const int32_t FIN_PIN = 9;
const int32_t DATA_PIN = 7;
const int32_t WRITE_PIN = 11;
const int32_t CS_PIN[NB_MATRIX] = { 25, 8, 12, 27, 13, 6, 17, 5, 22, 18 };

class HC1632;
class Gpio;
class BatmintonFactory : public GpioFactory
{
	public :
		BatmintonFactory(const std::string &);
		virtual ~BatmintonFactory();

		virtual int32_t status();
		virtual void majAffichage();
		
	protected:
		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

		int32_t _status;
		HC1632 * _matrix;
		std::chrono::time_point<std::chrono::high_resolution_clock> _last_valid_irq;
};

#endif /* GPIO_FACTORY_H */
