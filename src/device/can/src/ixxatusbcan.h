#ifndef IXXAT_USB_TO_CAN_H
#define IXXAT_USB_TO_CAN_H

#include "canbus.h"
#include <string>

// class PollDevice;
namespace Ixxat
{
	class UsbCan : public CAN::Bus
	{
		public:
			UsbCan(PollDevice *);
			virtual ~UsbCan();

			virtual int32_t writeData(uint16_t, uint8_t *, int32_t);
			virtual int32_t readData(uint16_t *, uint8_t *, int32_t);

			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();

		protected:
			virtual int32_t write(uint8_t *, int32_t);
			virtual int32_t read(uint8_t *, int32_t);
   };
}

#endif /* IXXAT_USB_TO_CAN_H */
