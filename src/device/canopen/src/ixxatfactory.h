#ifndef IXXAT_FACTORY_H
#define IXXAT_FACTORY_H

#include "pollfactory.h"
#include <string>

class PollDevice;
namespace Ixxat
{
	class CanAtNet;
	class Factory : public ::PollFactory
	{
		public:
			Factory();
			virtual ~Factory();
			
			virtual CanAtNet * canAtNet(const std::string &, int16_t);
			virtual CanAtNet * usbToCan(const std::string &);

		protected:
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);
	};
}

#endif /* IXXAT_FACTORY_H */