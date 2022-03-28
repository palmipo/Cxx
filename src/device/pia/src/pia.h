#ifndef CTRLPIA_H
#define CTRLPIA_H

#include <cstdint>

class CtrlPia : public Device
{
	public :
		CtrlPia()
		: Device(DeviceType::PIA) 
		{}

		virtual ~CtrlPia()
		{}

		virtual void write(uint8_t) = 0;
		virtual uint8_t read() = 0;
};

#endif /* CTRLPIA_H */
