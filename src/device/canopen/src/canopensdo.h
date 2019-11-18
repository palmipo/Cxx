#ifndef CANOPEN_SDO_H
#define CANOPEN_SDO_H

#include "canopensdobuffer.h"
#include <cstdint>

namespace CAN
{
	class CANOpen;
	class CANOpenSDO
	{
		public:
			CANOpenSDO(uint8_t, CAN::CANOpen *);

			virtual int32_t writeDictionary(uint16_t, uint8_t, uint8_t *, int32_t);
			virtual int32_t readDictionary(uint16_t, uint8_t, uint8_t *, int32_t);
			virtual int32_t abort(uint16_t, uint8_t, uint8_t, uint8_t, uint16_t);

		protected:
			virtual void error(CANOpenSdoBuffer);

		protected:
			uint8_t _node_id;
			CAN::CANOpen * _bus_can;
	};
}

#endif /* CANOPEN_SDO_H */
