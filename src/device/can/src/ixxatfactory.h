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
			
			virtual CanAtNet * canAtNet(const std::string &, int16_t = 19227, int32_t = 1000);
			virtual UsbCan * usbToCan(const std::string &);

		protected:
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);

			std::map < std::string, Device * > ctrlMap;
		};
}

#endif /* IXXAT_FACTORY_H */