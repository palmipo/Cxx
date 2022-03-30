#ifndef CTRLPIA_H
#define CTRLPIA_H

#include <cstdint>

class CtrlPIA : public Device
{
	public :
		CtrlPIA()
		: Device(Device::DeviceType_PIA) 
		{}

		virtual ~CtrlPIA()
		{}

		virtual void write(uint8_t) = 0;
		virtual uint8_t read() = 0;
};

#endif /* CTRLPIA_H */
