#ifndef CANOPEN_STATE_MACHINE_INIT_H
#define CANOPEN_STATE_MACHINE_INIT_H

#include <cstdint>
#include <map>
#include <thread>

namespace CAN
{
	class CANOpen;
	class CANOpenPDO;
	class CANOpenStateMachineInit
	{
		public:
			CANOpenStateMachineInit(uint8_t, CAN::CANOpen *);

			virtual CANOpenStateMachineReset * reset();

		protected:
			uint8_t _node_id;
			StateMachine _internal_state;
			std::thread * _thread[4];
			CAN::CANOpen * _bus_can;
	};
}

#endif /* CANOPEN_STATE_MACHINE_H */
