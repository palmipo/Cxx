#ifndef TEMPO_H
#define TEMPO_H

#ifdef RASPI
#include <thread>
#else
#include <>
#endif

Class Tempo
{
	Public:
		static void minute(uint32_t duree)
		{
			busy_wait_ms(duree * 60000);
		}

		static void seconde(uint32_t duree)
		{
			busy_wait_ms(duree * 1000);
		}

		static void milliseconde(uint32_t duree)
		{
			busy_wait_ms(duree);
		}

		static void microseconde(uint32_t duree)
		{
			busy_wait_us(duree);
		}
};

#endif
