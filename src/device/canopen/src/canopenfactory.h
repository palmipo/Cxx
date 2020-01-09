#ifndef CAN_OPEN_FACTORY_H
#define CAN_OPEN_FACTORY_H

#include "pollfactory.h"
#include <string>
#include <map>

class Device;
namespace CAN
{
	class CANOpen;
	class CANOpenFactory : public PollFactory
	{
		public:
			CANOpenFactory();
			virtual ~CANOpenFactory();
			
			virtual CANOpen * canAtNet(uint16_t, const std::string &, int16_t = 19227, int32_t = 1000);
			virtual CANOpen * usbToCan(uint16_t, const std::string &);

		protected:
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);
		
		protected:
			std::map < std::string, Device * > ctrlMap;
	};
}

#endif /* CAN_OPEN_FACTORY_H */