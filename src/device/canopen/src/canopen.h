#ifndef CANOPEN_H
#define CANOPEN_H

#include "device.h"
#include <map>

#define MNT_ID 0
#define EMGY_ID 0x1
#define PDO1_ID_RX 0x3
#define PDO1_ID_TX 0x4
#define PDO2_ID_RX 0x5
#define PDO2_ID_TX 0x6
#define PDO3_ID_RX 0x7
#define PDO3_ID_TX 0x8
#define PDO4_ID_RX 0x9
#define PDO4_ID_TX 0xA
#define SDO_ID_RX 0xB
#define SDO_ID_TX 0xC
#define GUARD_ID 0xE

namespace CAN
{
	class Bus;
	class CANOpenNMT;
	class CANOpenEMCY;
	class CANOpenSYNC;
	class CANOpenSDO;
	class CANOpenPDO;
	class CANOpenFifo;
	class CANOpenBuffer;
	class CANOpenStateMachine;
	class CANOpen : public Device
	{
		public:
			CANOpen(uint16_t, CAN::Bus *);
			virtual ~CANOpen();

			virtual CANOpenNMT  * nmt();
			virtual CANOpenEMCY * emergency();
			virtual CANOpenSDO  * sdo();
			virtual CANOpenPDO  * pdo(uint8_t);
			virtual CANOpenSYNC * sync();

			virtual int32_t writeData(CANOpenBuffer *);
			virtual int32_t readData(CANOpenBuffer *);

			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();

		// protected:
			// virtual PollDevice * get(uint8_t);

		protected:
			uint16_t _node_id;
			CAN::Bus * _bus_can;
			CANOpenStateMachine * _state_machine;
			CANOpenNMT  * _map_nmt;
			CANOpenEMCY * _map_emergency;
			CANOpenSDO  * _map_sdo;
			CANOpenSYNC * _map_sync;
			std::map < uint8_t, CANOpenPDO  * > _map_pdo;
			std::map < uint8_t , CANOpenFifo  * > _map_fifo;
	};
}

#endif /* CANOPEN_H */
