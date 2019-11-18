#ifndef HD44780_H
#define HD44780_H

#include "batratypes.h"

class HD44780IO;
class HD44780
{
public:
	HD44780(HD44780IO * ctrl);
	~HD44780();

	void setText(s8 * txt, u8 len);
	void clear();
	void returnHome();
	void setEntryMode(u8 increment, u8 shift);
	void setDisplayControl(u8 displayOn, u8 cursorOn, u8 blinkingCursor);
	void setCursorDisplayShift(u8 displayShift, u8 shiftToRight);
	void setFunction(u8 dataLength, u8 numberLine, u8 characterFont);
	void setCGRAMAdrress(u8 address);
	void setDDRAMAdrress(u8 address);
	u8   readAddress();
	void writeData(u8 data);
	u8 readData();
	void setPosition(u8 line, u8 column);

protected:
	void init ();
	void reset();

protected:
	HD44780IO * _ctrl;
};

#endif
