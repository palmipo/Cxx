#ifndef CANOPEN_MNT_H
#define CANOPEN_MNT_H

#include <cstdint>

namespace std
{
	class thread;
}
namespace CAN
{
	class CANOpen;
	class CANOpenNMT
	{
		public:
			CANOpenNMT(uint8_t, CAN::CANOpen *);

			virtual int32_t start();
			virtual int32_t stop();
			virtual int32_t preOperational();
			virtual int32_t reset();
			virtual int32_t resetCommunication();

		protected:
			virtual int32_t command(uint8_t);

		protected:
			uint8_t _node_id;
			CAN::CANOpen * _bus_can;
			std::thread * _thread[3];
	};
}

#endif /* CANOPEN_MNT_H */
