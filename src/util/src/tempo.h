#ifndef TEMPO_H
#define TEMPO_H

#ifdef RASPI
#include <thread>
#endif

class Tempo
{
	public:
		static void minutes(uint32_t duree)
		{
#ifdef RASPI
			std::this_thread::sleep_for(std::chrono::minutes(duree));
#else
			busy_wait_ms(duree * 60000);
#endif
		}

		static void secondes(uint32_t duree)
		{
#ifdef RASPI
			std::this_thread::sleep_for(std::chrono::seconds(duree));
#else
			busy_wait_ms(duree * 1000);
#endif
		}

		static void millisecondes(uint32_t duree)
		{
#ifdef RASPI
			std::this_thread::sleep_for(std::chrono::milliseconds(duree));
#else
			busy_wait_ms(duree);
#endif
		}

		static void microsecondes(uint32_t duree)
		{
#ifdef RASPI
			std::this_thread::sleep_for(std::chrono::microseconds(duree));
#else
			busy_wait_us(duree);
#endif
		}
};

#endif
