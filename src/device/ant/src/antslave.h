#ifndef ANT_SLAVE_H
#define ANT_SLAVE_H

#include "antprofile.h"

namespace ANT
{
	class Ant;
	class Slave : public Profile
	{
		public:
			Slave(uint8_t, Ant *);
			virtual ~Slave();

			virtual void init();

		protected:
			virtual void unassignedChannelEventRecv(uint8_t);
			virtual void assignedChannelEventRecv(uint8_t);
			virtual void channelPeriodEventRecv(uint8_t);
			virtual void searchTimeoutEventRecv(uint8_t);
			virtual void channelRfFrequencyEventRecv(uint8_t);
			virtual void searchWaveformEventRecv(uint8_t);
			virtual void channelOpenedEventRecv(uint8_t);
			virtual void channelClosedEventRecv(uint8_t);
			virtual void channelStatusEventRecv(uint8_t);
			virtual void channelIdEventRecv(uint8_t);
			virtual void requestedMessageEventRecv(uint8_t);

			virtual void broadcastDataEventRecv(uint8_t);
			virtual void acknowledgedDataEventRecv(uint8_t);
			virtual void burstTransfertDataEventRecv(uint8_t);
			virtual void advancedBurstDataEventRecv(uint8_t);

			virtual int32_t specialEventPageRecv(uint8_t, uint8_t *, int32_t) = 0;
	};
}

#endif /* ANT_H */

