#ifndef HD44780_H
#define HD44780_H

#include <cstdint>

class HD44780IO;
class HD44780
{
public:
	HD44780(HD44780IO * ctrl, uint32_t ligne, uint32_t colonne);
	~HD44780();

	void setText(int8_t * txt, uint8_t len);
	void clear();
	void returnHome();
	void setEntryMode(uint8_t increment, uint8_t shift);
	void setDisplayControl(uint8_t displayOn, uint8_t cursorOn, uint8_t blinkingCursor);
	void setCursorDisplayShift(uint8_t displayShift, uint8_t shiftToRight);
	void setFunction(uint8_t dataLength, uint8_t numberLine, uint8_t characterFont);
	void setCGRAMAdrress(uint8_t address);
	void setDDRAMAdrress(uint8_t address);
	uint8_t readAddress();
	void writeData(uint8_t data);
	uint8_t readData();
	void setPosition(uint8_t line, uint8_t column);

protected:
	void init ();
	void reset();

protected:
	HD44780IO * _ctrl;
uint32_t _nb_ligne;
uint32_t _nb_colonne;
};

#endif
