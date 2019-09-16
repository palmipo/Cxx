#ifndef __ONE_WIRE_H__
#define __ONE_WIRE_H__

class oneWire
{
	public:
		oneWire();
		virtual ~oneWire();
		
		void reset();
		void send_bit();
		void recv_bit();
};

#endif
