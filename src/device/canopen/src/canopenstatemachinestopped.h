#ifndef CANOPEN_STATE_MACHINE_H
#define CANOPEN_STATE_MACHINE_H

#include <cstdint>
#include <map>
#include <thread>

namespace CAN
{
	class CANOpen;
	class CANOpenPDO;
	class CANOpenStateMachine
	{
		enum StateMachine
		{
			Initialization = 0
			, PreOperational
			, Operational
			, Stopped
		};

		public:
			CANOpenStateMachine(uint8_t, CAN::CANOpen *);

			virtual void start();
			virtual void stop();
			virtual void preOperational();
			virtual void reset();
			virtual void resetCommunication();

		protected:
			uint8_t _node_id;
			StateMachine _internal_state;
			std::thread * _thread[3];
			CAN::CANOpen * _bus_can;
	};
}

#endif /* CANOPEN_STATE_MACHINE_H */
