#ifndef CANOPEN_SYNC_H
#define CANOPEN_SYNC_H

namespace CAN
{
	class CANOpen;
	class CANOpenSYNC
	{
		public:
			CANOpenSYNC(CAN::CANOpen *);
			
			void sendSync();

		protected:
			CAN::CANOpen * _bus_can;
	};
}

#endif /* CANOPEN_SYNC_H */
