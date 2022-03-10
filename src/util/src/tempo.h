#ifndef RASPITEMPO_H
#define RASPITEMPO_H

#include <thread>

class Tempo
{
	public:
		static void minutes(uint32_t duree)
		{
			std::this_thread::sleep_for(std::chrono::minutes(duree));
		}

		static void secondes(uint32_t duree)
		{
			std::this_thread::sleep_for(std::chrono::seconds(duree));
		}

		static void millisecondes(uint32_t duree)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(duree));
		}

		static void microsecondes(uint32_t duree)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(duree));
		}
};

#endif
