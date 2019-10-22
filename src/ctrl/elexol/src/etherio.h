#ifndef ETHERIO_H
#define ETHERIO_H

#include "batratypes.h"
#include "pia.h"
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Socket
{
	class SocketUdp;
}
class EtherIO : public PollDevice
{
public:
	EtherIO(Socket::SocketUdp *);
	virtual ~EtherIO();

	virtual u8 getDirection(u8);
	virtual void setDirection(u8, u8);

	virtual u8 getPullup(u8);
	virtual void setPullup(u8, u8);

	virtual u8 getThreshold(u8);
	virtual void setThreshold(u8, u8);

	virtual u8 getSchmitt(u8);
	virtual void setSchmitt(u8, u8);

	virtual void set(u8, u8);
	virtual u8 get(u8);

	virtual void identifyUnit();
	virtual void resetModule();
	
	virtual void setAutoScan(u8, u8=1, u16=1/*, u8 *, u8 *, u16*/);

	virtual u16 readEEPROM(u8);
	virtual void writeEEPROM(u8, u8, u8);
	virtual void eraseEEPROM(u8);
	virtual void enableEEPROM();
	virtual void disableEEPROM();

protected:
	Socket::SocketUdp * _socket;
};

#endif /* ETERHIO_H */
