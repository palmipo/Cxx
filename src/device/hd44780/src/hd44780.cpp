#include "hd44780.h"
#include "hd44780io.h"
#include <iostream>
#include <poll.h>

HD44780::HD44780(HD44780IO * ctrl)
: _ctrl(ctrl)
{
	init();
	clear();
}

HD44780::~HD44780()
{}

void HD44780::setText(int8_t * txt, uint8_t len)
{
	for (uint8_t i=0; i<len; ++i)
	{
		writeData(txt[i]);
	}
}

void HD44780::clear()
{
	_ctrl->cmd(0x01);
}

void HD44780::returnHome()
{
	_ctrl->cmd(0x02);
}

void HD44780::setEntryMode(uint8_t increment, uint8_t shift)
{
	_ctrl->cmd(0x04 | ((increment & 0x01) << 1) | (shift & 0x01));
}

void HD44780::setDisplayControl(uint8_t displayOn, uint8_t cursorOn, uint8_t blinkingCursor)
{
	uint8_t byte = 0x08 | ((displayOn & 0x1) << 2) | ((cursorOn & 0x1) << 1) | (blinkingCursor & 0x1);
	_ctrl->cmd(byte);
}

void HD44780::setCursorDisplayShift(uint8_t displayShift, uint8_t shiftToRight)
{
	uint8_t byte = 0x10 | ((displayShift & 0x1) << 3) | ((shiftToRight & 0x1) << 2);
	_ctrl->cmd(byte);
}

void HD44780::setFunction(uint8_t dataLength, uint8_t numberLine, uint8_t characterFont)
{
	uint8_t byte = 0x20 | ((dataLength & 0x1) << 4) | ((numberLine & 0x1) << 3) | ((characterFont & 0x1) << 2);
	_ctrl->cmd(byte);
}

void HD44780::setCGRAMAdrress(uint8_t address)
{
	uint8_t byte = 0x40 | (address & 0x3F);
	_ctrl->cmd(byte);
}

void HD44780::setDDRAMAdrress(uint8_t address)
{
	uint8_t byte = 0x80 | (address & 0x7F);
	_ctrl->cmd(byte);
}

uint8_t HD44780::readAddress()
{
	return _ctrl->readCmd();
}

void HD44780::writeData(uint8_t data)
{
	_ctrl->data(data);
}

uint8_t HD44780::readData()
{
	return _ctrl->readData();
}

void HD44780::setPosition(uint8_t line, uint8_t column)
{
	uint8_t byte = 0;
	switch(line)
	{
		case 0: // 0x00
			byte = column;
			break;
		case 1: // 0x40
			byte = 0X40 | column;
			break;
		case 2: // 0x14
			byte = 0x14 | column;
			break;
		case 3: // 0x54
			byte = 0X54 | column;
			break;
	}
	setDDRAMAdrress(byte);
}

void HD44780::init ()
{
	reset(); // Call LCD reset
	setFunction(0, 1, 0); // 4-bit mode - 2 lines - 5x8 font.
	setDisplayControl(1, 0, 0); // Display no cursor - no blink.
	setEntryMode(1, 0); // Automatic Increment - No Display shift.
	setCursorDisplayShift(0, 0);
}

void HD44780::reset()
{
	//_ctrl->cmd(3);
	_ctrl->write(3, 0, 0);
	//poll(0, 0, 45);
	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	//_ctrl->cmd(3);
	_ctrl->write(3, 0, 0);
	//poll(0, 0, 45);
	std::this_thread::sleep_for(std::chrono::microseconds(100));

	//_ctrl->cmd(3);
	_ctrl->write(3, 0, 0);
	//poll(0, 0, 15);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//_ctrl->cmd(2);
	_ctrl->write(2, 0, 0);
	//poll(0, 0, 15);
std::this_thread::sleep_for(std::chrono::milliseconds(500))
}
