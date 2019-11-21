#ifndef lcd2004_H
#define lcd2004_H

#include "batratypes.h"
#include "hd44780io.h"

class I2C;
class PIA;
class HD44780;
class lcd2004 : public HD44780IO
{
public:
	lcd2004(I2C *i2c);
	virtual ~lcd2004();

	virtual void setBackLight(u8 value);
	virtual HD44780 * lcd();

private:
	virtual void cmd (u8 value);
	virtual void data (u8 value);
	virtual u8   readCmd ();
	virtual u8   readData ();
	virtual void write (u8 value, u8 rs, u8 rw_);

	virtual bool isBusy(u8 *addressCounter = 0);
	virtual void enableBit(u8);

private:
	PIA *_pia;
	u8 _backLight;
	HD44780 *_afficheur;
};

#endif
