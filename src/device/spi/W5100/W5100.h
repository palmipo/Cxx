#ifndef __W5100_H__
#define __W5100_H__

class W5100
{
public:
	W5100();
	virtual ~W5100();

	void setGateway(u8 * gar);
	void setSubnetMaskAddress(u8 * subr);
	void setSourceHardwareAddress(u8 * shar);
	void setSourceIPAddress(u8 * sipr);
	void setInterrupt(u8 ir);
	void setRetryTime(u8 * rtr);
	void setRetryCount(u8 * rcr);
	void setRxMemorySize(u8 * rmsr);
	void setTxMemorySize(u8 tmsr);
	void setAuthenticationTypePPPoe(u8 * patr);
	void setPTimer(u8 ptimer);
	void setPMagic(u8 pmagic);
	void setUnreachableIpAddress(u8 * uipr);
	void setUnreachablePort(u8 * uport);

private:
	W5100Socket _socket[4];
};

#endif
