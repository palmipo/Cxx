#ifndef ANT_TEMPE_H
#define ANT_TEMPE_H

#include "antslave.h"

namespace ANT
{
	class Ant;
	class Tempe : public Slave
	{
		public:
			Tempe(uint8_t, uint8_t, Ant *);
			virtual ~Tempe();

			virtual int32_t specialEventPageRecv(uint8_t, uint8_t *, int32_t);

		protected:
			// page 0
			uint8_t Transmission_Info;
			uint32_t Supported_Pages;

			// page 1
			uint8_t event_count;
			int16_t lowest_temperature;
			int16_t highest_temperature;
			int16_t current_temperature;
	};
}

#endif
