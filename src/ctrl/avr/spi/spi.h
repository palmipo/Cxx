#ifndef __SPI_H__
#define __SPI_H__

class SPI
{
public:
	SPI();
	~SPI();

	void setMaster();
	void setSlave();

	void setMode(unsigned char mode);
	void setClockRate(unsigned char rate);
	void setDataOrder(unsigned char order);

	void send(unsigned char * buffer, unsigned char length);
	void recv(unsigned char * buffer, unsigned char length);

	void setRecvCallback(void (*callback)(unsigned char));
};

#endif
