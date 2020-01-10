#ifndef ART_NET_H
#define ART_NET_H

#include <cstdint>

namespace Socket
{
	class SocketUdp;
}
namespace Dmx
{
	class Master;
}
class ArtNet
{
	public:
		ArtNet(Socket::SocketUdp*);
		
		virtual Dmx::Master * addMaster(uint8_t, uint16_t);
};

#endif
