#ifndef IXXAT_FACTORY_H
#define IXXAT_FACTORY_H

#include "pollfactory.h"
#include <string>

class Device;
class PollDevice;
namespace Ixxat
{
	class UsbCan;
	class CanAtNet;
	class Factory : public PollFactory
	{
		public:
			Factory();
			virtual ~Factory();
			
			virtual CanAtNet * canAtNet(uint16_t, const std::string &, int16_t);
			virtual UsbCan * usbToCan(uint16_t, const std::string &);

		protected:
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);

			std::map < std::string, Device * > ctrlMap;
		};
}

#endif /* IXXAT_FACTORY_H */