#ifndef TEMPO_H
#define TEMPO_H

#include <hardware/timer.h>

class Tempo
{
	public:
		static void minutes(uint32_t duree)
		{
			busy_wait_ms(duree * 60000);
		}

		static void secondes(uint32_t duree)
		{
			busy_wait_ms(duree * 1000);
		}

		static void millisecondes(uint32_t duree)
		{
			busy_wait_ms(duree);
		}

		static void microsecondes(uint32_t duree)
		{
			busy_wait_us(duree);
		}
};

#endif
