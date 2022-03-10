/*
https://robot-electronics.co.uk/htm/usb_i2c_tech.htm
*/

#ifndef USB_I2C_H
#define USB_I2C_H

#include "ctrli2c.h"

class RS232;
class UsbI2C : public CtrlI2C
{
	public:
		UsbI2C(RS232 *);

		virtual uint8_t getVersion();

		virtual void set (uint8_t addr, uint8_t* buf, int32_t len);
		virtual void get (uint8_t addr, uint8_t* buf, int32_t len);
		virtual void transfer (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len);

	protected:
		RS232 * _uart;
};

#endif
