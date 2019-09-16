#ifndef CANOPEN_EMCY_H
#define CANOPEN_EMCY_H

// #include "canopenfifo.h"
#include <cstdint>

namespace CAN
{
	class CANOpen;
	class CANOpenEMCY //: public CANOpenFifo
	{
		public:
			CANOpenEMCY(uint8_t, CAN::CANOpen *);

			virtual int32_t read(uint16_t *, uint8_t *, uint8_t *, int32_t);
			virtual int32_t write(uint8_t , uint8_t , uint8_t , uint8_t , uint8_t , uint8_t , uint8_t , uint8_t);

		protected:
			uint8_t _node_id;
			CAN::CANOpen * _bus_can;
	};
}

#endif /* CANOPEN_EMCY_H */
