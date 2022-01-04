#ifndef HD44780_IO_H
#define HD44780_IO_H

#include <cstdint>

class HD44780IO
{
public:
	HD44780IO() {}
	virtual ~HD44780IO() {}

	virtual void cmd (uint8_t value) = 0;
	virtual void data (uint8_t value) = 0;
	virtual uint8_t   readCmd () = 0;
	virtual uint8_t   readData () = 0;
	virtual void write (uint8_t value, uint8_t rs, uint8_t rw_) = 0;
	virtual void setBackLight(uint8_t value) = 0;
};

#endif
