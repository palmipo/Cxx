#ifndef ANT_SPEEDCADENCE_H
#define ANT_SPEEDCADENCE_H

#include "antslave.h"

namespace ANT
{
	class Ant;
	class SpeedCadence : public Slave
	{
		public:
			SpeedCadence(uint8_t, uint8_t, Ant *);
			virtual ~SpeedCadence();

			virtual int32_t specialEventPageRecv(uint8_t, uint8_t *, int32_t);
	};
}

#endif
