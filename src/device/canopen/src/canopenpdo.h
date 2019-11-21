#ifndef CANOPEN_PDO_H
#define CANOPEN_PDO_H

#include "canopenbuffer.h"
#include <cstdint>

namespace CAN
{
	class CANOpen;
	class CANOpenFifo;
	class CANOpenBuffer;
	class CANOpenPDO
	{
		public:
			CANOpenPDO(uint8_t, uint8_t, CAN::CANOpen *);

			virtual int32_t read(uint8_t * data, int32_t length);
			virtual int32_t write(uint8_t * data, int32_t length);

			virtual void send();
			virtual void sendCyclic(uint8_t * data, int32_t length, int32_t period);
			virtual int32_t cyclic();

		protected:
			int32_t _cyclic;
			uint8_t _pdo_id;
			uint8_t _node_id;
			CANOpen * _bus_can;
			CANOpenFifo * _fifo_in;
			CANOpenBuffer _out;
	};
}

#endif /* CANOPEN_PDO_H */
