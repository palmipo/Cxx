#ifndef IXXAT_USB_TO_CAN_H
#define IXXAT_USB_TO_CAN_H

#include "canbus.h"
#include <string>

namespace Ixxat
{
	class UsbCan : public CAN::Bus
	{
		public:
			UsbCan(uint16_t, PollDevice *);
			virtual ~UsbCan();

			virtual int32_t writeData(uint16_t, uint8_t *, int32_t);
			virtual int32_t readData(uint16_t *, uint8_t *, int32_t, int32_t = 10, int32_t = 1000);

			virtual int32_t actionIn(uint8_t *, int32_t);
			virtual int32_t actionOut(uint8_t *, int32_t);
			virtual int32_t actionError(uint8_t *, int32_t);
	};
}

#endif /* IXXAT_USB_TO_CAN_H */
