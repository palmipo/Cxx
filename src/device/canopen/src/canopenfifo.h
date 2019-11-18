#ifndef CAN_OPEN_FIFO_H
#define CAN_OPEN_FIFO_H

#include "canopenbuffer.h"
#include <queue>

namespace CAN
{
	class CANOpenFifo
	{
		public:
			CANOpenFifo();
			virtual ~CANOpenFifo();

			virtual void lastIn(CANOpenBuffer * buffer);
			virtual CANOpenBuffer * firstOut(int32_t max_retry = 15, int32_t timeout = 1000);

		protected:
			std::queue < CANOpenBuffer * > _fifo;
	};
}

#endif /* CAN_OPEN_FIFO_H */
