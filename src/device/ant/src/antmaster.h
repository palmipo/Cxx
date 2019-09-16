#ifndef ANT_MASTER_H
#define ANT_MASTER_H

#include "antprofile.h"

namespace ANT
{
	class Ant;
	class Master : public Profile
	{
		public:
			Master(uint8_t channel_id, Ant *);
			virtual ~Master();

			virtual void init();

		protected:
			static void transmitPowerCallback(uint8_t response_code, void * data);
	};
}

#endif /* ANT_MASTER_H */

