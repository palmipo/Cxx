#ifndef IXXAT_CAN_AT_NET_H
#define IXXAT_CAN_AT_NET_H

#include "polldevice.h"
#include "canbuffer.h"
#include <string>
#include <vector>
#include <queue>

namespace Socket
{
	class SocketTcp;
}
namespace Ixxat
{
	class CanAtNet : public ::PollDevice
	{
		public:
			CanAtNet(Socket::SocketTcp *);
			virtual ~CanAtNet();

			virtual int32_t writeData(uint16_t, uint8_t *, int32_t);
			virtual int32_t readData(uint16_t *, uint8_t *, int32_t);

			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();
			virtual void close();

		protected:
			virtual int32_t writeCommand(const std::string &);

		protected:
			Socket::SocketTcp * _socket;
			std::queue < CanBuffer > _fifo;
	};
}

#endif /* IXXAT_CAN_AT_NET_H */
