#ifndef CAN_OPEN_SDO_BUFFER_H
#define CAN_OPEN_SDO_BUFFER_H

#include "canopenbuffer.h"

namespace CAN
{
	class CANOpenSdoBuffer : public PollBuffer
	{
		public:
			CANOpenSdoBuffer();

			uint8_t  pdo_id;
			uint8_t  node_id;
			uint8_t  command;
			uint16_t index;
			uint8_t  subindex;
		
			int32_t fromCANOpenBuffer(CANOpenBuffer *);
			int32_t toCANOpenBuffer(CANOpenBuffer *);
	};
}

#endif /* CAN_OPEN_SDO_BUFFER_H */
