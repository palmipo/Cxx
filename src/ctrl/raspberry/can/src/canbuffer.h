#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H

#include "pollbuffer.h"

namespace CAN
{
	class CANBuffer : public PollBuffer
	{
		public:
			CANBuffer();

			uint16_t cob_id;
	};
}

#endif /* CAN_BUFFER_H */
