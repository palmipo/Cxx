#ifndef I2C_H
#define I2C_H

#include "batratypes.h"

class I2C
{
public:
	I2C();
	I2C(u8 own_address);
	~I2C();

	u8 set(
		u8 twi_address,
		u8 * twi_snd_buffer,
		u8 twi_nb_snd);

	u8 get(
		u8 twi_address,
		u8 * twi_rcv_buffer,
		u8 twi_nb_rcv);

	u8 transfert(
		u8 twi_address,
		u8 *twi_snd_buffer,
		u8 twi_nb_snd,
		u8 *twi_rcv_buffer,
		u8 twi_nb_rcv);

private:
	u8 _own_address;
	u8 status();
};

#endif /* I2C */

