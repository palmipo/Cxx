#ifndef ADA772_H
#define ADA772_H

#include "hd44780io.h"

class MCP23017;
class ADA772 : public HD44780IO
{
public:
	ADA772(MCP23017 * ctrl);
	virtual ~ADA772();

	virtual void setSelectCallback(void (*)(bool));
	virtual void setUpCallback(void (*)(bool));
	virtual void setRightCallback(void (*)(bool));
	virtual void setDownCallback(void (*)(bool));
	virtual void setLeftCallback(void (*)(bool));
	virtual void setButtonsCallback(void (*)(uint8_t, void *), void *);

	virtual void setBackLight(uint8_t value);

	virtual uint8_t scrute();

private:
	virtual void cmd (uint8_t);
	virtual void data (uint8_t);
	virtual bool isBusy(uint8_t * addressCounter = 0);
	virtual void enableBit(uint8_t);
	virtual uint8_t readCmd();
	virtual uint8_t readData();
	virtual void write (uint8_t value, uint8_t rs, uint8_t rw_);

private:
	MCP23017 *_pia;
	void *_user_data;
	uint8_t _backlight;

	void (*_selectTriggered)(bool);
	void (*_upTriggered)(bool);
	void (*_rightTriggered)(bool);
	void (*_downTriggered)(bool);
	void (*_leftTriggered)(bool);
	void (*_buttonTriggered)(uint8_t, void *);
};

#endif
