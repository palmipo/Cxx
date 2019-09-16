#ifndef CANOPEN_MSG_H
#define CANOPEN_MSG_H

#include <cstdint>

namespace CAN
{
	class CANOpen;
	class CANOpenFifo;
	class CANOpenMsg : public PollDevice
	{
		public:
			CANOpenMsg(uint8_t, uint8_t, CAN::CANOpen *);

			virtual int32_t read(uint8_t * data, int32_t length);
			virtual int32_t write(uint8_t * data, int32_t length);

		protected:
			int32_t _cyclic;
			uint8_t _pdo_id;
			uint8_t _node_id;
			CAN::CANOpen * _bus_can;
			std::map < uint8_t, CANOpenFifo * > _fifo;
	};
}

#endif /* CANOPEN_PDO_H */
