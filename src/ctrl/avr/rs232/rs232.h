#ifndef __RS232_H__
#define __RS232_H__

class RS232
{
public:
	RS232();
	~RS232();

	void init(unsigned short baud, unsigned char parity, unsigned char n_bit, unsigned char n_stop);
	void send(unsigned char * octets, unsigned char length);
	void recv(unsigned char * octets, unsigned char length);
	void setRecvCallback(void (*callback)(unsigned char));
};

#endif
