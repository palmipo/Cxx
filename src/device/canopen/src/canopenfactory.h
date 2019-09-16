#ifndef CAN_OPEN_FACTORY_H
#define CAN_OPEN_FACTORY_H

#include "pollfactory.h"
#include <string>
#include <map>

class TowerDevice;
namespace CAN
{
	class CANOpen;
	class CANOpenFactory : public PollFactory
	{
		public:
			CANOpenFactory();
			virtual ~CANOpenFactory();
			
			virtual CANOpen * canAtNet(const std::string &, int16_t, int32_t);
			virtual CANOpen * usbToCan(const std::string &);

		protected:
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);
		
		protected:
			std::map < std::string, TowerDevice * > ctrlMap;
	};
}

#endif /* CAN_OPEN_FACTORY_H */