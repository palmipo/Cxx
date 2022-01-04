#ifndef LCD2004_H
#define LCD2004_H

#include "hd44780io.h"

class PCF8574AT;
class LCD2004 : public HD44780IO
{
public:
	LCD2004(PCF8574AT *i2c);
	virtual ~LCD2004();

	virtual void setBackLight(uint8_t value);

private:
	virtual void cmd (uint8_t value);
	virtual void data (uint8_t value);
	virtual uint8_t   readCmd ();
	virtual uint8_t   readData ();
	virtual void write (uint8_t value, uint8_t rs, uint8_t rw_);

	virtual bool isBusy(uint8_t *addressCounter = 0);
	virtual void enableBit(uint8_t);

private:
	PCF8574AT *_pia;
	uint8_t _backLight;
};

#endif
