#ifndef TCA9548A_H
#define TCA9548A_H

#include "devicei2c.h"

/* i2c_addr = 0xE0 */

class CtrlI2C;
class TCA9548A : public DeviceI2C
{
	public:
		TCA9548A(uint8_t, CtrlI2C *);
		void select(uint8_t);
};

#endif /* TCA9548A_H */
