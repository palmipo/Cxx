#ifndef CANOPEN_GUARD_H
#define CANOPEN_GUARD_H

// #include "canopenfifo.h"
#include <cstdint>

namespace CAN
{
	class CANOpen;
	class CANOpenGuard// : public CANOpenFifo
	{
		public:
			CANOpenGuard(uint8_t, CAN::CANOpen *);

			virtual int32_t read(uint8_t *);

		protected:
			uint8_t _node_id;
			CAN::CANOpen * _bus_can;
	};
}

#endif /* CANOPEN_GUARD_H */
