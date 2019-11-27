#ifndef CAN_BUS_H
#define CAN_BUS_H

#include "device.h"
#include <queue>

class PollDevice;
namespace CAN
{
	class CANBuffer;
	class Bus : public Device
	{
		public:
			Bus(uint16_t cob_id, PollDevice * device)
			: Device()
			, _cob_id(cob_id)
			{}

			virtual int32_t writeData(uint16_t, uint8_t *, int32_t) = 0;
			virtual int32_t readData(uint16_t *, uint8_t *, int32_t, int32_t = 10, int32_t = 1000) = 0;

			virtual int32_t writeData(CANBuffer *);
			virtual int32_t readData(CANBuffer *, int32_t = 10, int32_t = 1000);

		protected:
			uint16_t _cob_id;
			std::queue < CANBuffer * > _fifo;
			PollDevice * _device;
	};
}

#endif /* CANBUS_H */
