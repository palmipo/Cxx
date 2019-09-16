#ifndef HD44780_IO_H
#define HD44780_IO_H

#include "batratypes.h"


class HD44780IO
{
public:
	HD44780IO() {}
	virtual ~HD44780IO() {}

	virtual void cmd (u8 value) = 0;
	virtual void data (u8 value) = 0;
	virtual u8   readCmd () = 0;
	virtual u8   readData () = 0;
	virtual void write (u8 value, u8 rs, u8 rw_) = 0;
	virtual void setBackLight(u8 value) = 0;
};

#endif
