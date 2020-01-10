#ifndef DMX_MASTER_H
#define DMX_MASTER_H

namespace Dmx
{
class Master
{
	public:
		Master(Socket::SocketUdp*);
		
		virtual Dmx::Slave * addSlave(uint8_t, uint8_t);
};

#endif
