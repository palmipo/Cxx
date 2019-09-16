#ifndef ADA772_H
#define ADA772_H

#include "batratypes.h"
#include "hd44780io.h"

class I2C;
class MCP23017;
class HD44780;
class ADA772 : public HD44780IO
{
public:
	ADA772(I2C * ctrl);
	virtual ~ADA772();

	virtual HD44780 *LCD();

	virtual void setSelectCallback(void (*callback)(bool));
	virtual void setUpCallback(void (*callback)(bool));
	virtual void setRightCallback(void (*callback)(bool));
	virtual void setDownCallback(void (*callback)(bool));
	virtual void setLeftCallback(void (*callback)(bool));
	virtual void setButtonsCallback(void (*callback)(u8, void *), void *user_data);

	virtual void setBackLight(u8 value);

	virtual u8 scrute();

private:
	virtual void cmd (u8);
	virtual void data (u8);
	virtual bool isBusy(u8 * addressCounter = 0);
	virtual void enableBit(u8);
	virtual u8 readCmd();
	virtual u8 readData();
	virtual void write (u8 value, u8 rs, u8 rw_);

private:
	MCP23017 *_pia;
	HD44780 *_afficheur;
	void *_user_data;
	u8 _backlight;

	void (*_selectTriggered)(bool);
	void (*_upTriggered)(bool);
	void (*_rightTriggered)(bool);
	void (*_downTriggered)(bool);
	void (*_leftTriggered)(bool);
	void (*_buttonTriggered)(u8, void *);
};

#endif
