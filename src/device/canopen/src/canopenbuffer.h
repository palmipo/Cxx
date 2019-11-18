#ifndef CAN_OPEN_BUFFER_H
#define CAN_OPEN_BUFFER_H

#include "canbuffer.h"

namespace CAN
{
	class CANOpenBuffer : public PollBuffer
	{
		public:
			CANOpenBuffer();

			uint8_t  pdo_id;
			uint8_t  node_id;
		
			int32_t fromCANBuffer(CANBuffer *);
			int32_t toCANBuffer(CANBuffer *);
	};
}

#endif /* CAN_OPEN_BUFFER_H */
