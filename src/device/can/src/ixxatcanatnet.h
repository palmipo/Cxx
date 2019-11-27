#ifndef IXXAT_CAN_AT_NET_H
#define IXXAT_CAN_AT_NET_H

#include "canbus.h"
#include "canbuffer.h"
#include <string>
#include <queue>

// class PollDevice;
namespace Ixxat
{
	class CanAtNet : public CAN::Bus
	{
		public:
			CanAtNet(uint16_t, PollDevice *);
			virtual ~CanAtNet();

			virtual void init(int32_t);

			virtual int32_t writeData(uint16_t, uint8_t *, int32_t);
			virtual int32_t readData(uint16_t *, uint8_t *, int32_t, int32_t = 10, int32_t = 1000);

			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();

		protected:
			virtual int32_t writeCommand(const std::string &, int32_t = 10, int32_t = 1000);
			virtual int32_t write(uint8_t *, int32_t);
			virtual int32_t read(uint8_t *, int32_t);

		protected:
			std::queue < std::vector < std::string > > _cmd_fifo;
	};
}

#endif /* IXXAT_CAN_AT_NET_H */
