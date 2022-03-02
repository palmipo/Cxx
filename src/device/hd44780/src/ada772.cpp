#include "ada772.h"
#include "mcp23017.h"
#include "hd44780.h"
#include "tempo.h"

union ST_LCD
{
	struct ST_LCD_BIT
	{
		uint8_t BACKLIGHT:1;	// bit 0
		uint8_t DB7:1;
		uint8_t DB6:1;
		uint8_t DB5:1;
		uint8_t DB4:1;
		uint8_t EN:1;
		uint8_t RW_:1;
		uint8_t RS:1;	//  bit 7
	} bit;
	uint8_t octet;
};

ADA772::ADA772(MCP23017 * ctrl)
: HD44780IO()
, _pia(ctrl)
, _selectTriggered(0)
, _upTriggered(0)
, _rightTriggered(0)
, _downTriggered(0)
, _leftTriggered(0)
, _buttonTriggered(0)
, _user_data(0)
, _backlight(0)
{}

ADA772::~ADA772()
{}

void ADA772::setSelectCallback(void (*callback)(bool))
{
	_selectTriggered = callback;
}

void ADA772::setUpCallback(void (*callback)(bool))
{
	_upTriggered = callback;
}

void ADA772::setRightCallback(void (*callback)(bool))
{
	_rightTriggered = callback;
}

void ADA772::setDownCallback(void (*callback)(bool))
{
	_downTriggered = callback;
}

void ADA772::setLeftCallback(void (*callback)(bool))
{
	_leftTriggered = callback;
}

void ADA772::setButtonsCallback(void (*callback)(uint8_t, void *), void *user_data)
{
	_buttonTriggered = callback;
	_user_data = user_data;
}

void ADA772::setBackLight(uint8_t value)
{
	_backlight = value ? 1 : 0;
	_pia->set(0, value ? 0 : 0xC0);
}

uint8_t ADA772::scrute()
{
	uint8_t value = _pia->getIrq(0);

	if (_buttonTriggered)
	{
		_buttonTriggered(value, _user_data);
	}

	if (value & 0x01)
	{
		if (_selectTriggered) _selectTriggered(true);
	}
	else if (value & 0x02)
	{
		if (_rightTriggered) _rightTriggered(true);
		}
	else if (value & 0x04)
	{
		if (_downTriggered) _downTriggered(true);
	}
	else if (value & 0x08)
	{
		if (_upTriggered) _upTriggered(true);
	}
	else if (value & 0x10)
	{
		if (_leftTriggered) _leftTriggered(true);
	}

	return value;
}

void ADA772::cmd(uint8_t cmd)
{
	ST_LCD lcd;

	lcd.octet = 0;
	lcd.bit.BACKLIGHT = _backlight;
	lcd.bit.DB7=(cmd & 0X80)?1:0;
	lcd.bit.DB6=(cmd & 0X40)?1:0;
	lcd.bit.DB5=(cmd & 0X20)?1:0;
	lcd.bit.DB4=(cmd & 0X10)?1:0;
	enableBit(lcd.octet);

	while(isBusy());

	lcd.octet = 0;
	lcd.bit.BACKLIGHT = _backlight;
	lcd.bit.DB7=(cmd & 0X08)?1:0;
	lcd.bit.DB6=(cmd & 0X04)?1:0;
	lcd.bit.DB5=(cmd & 0X02)?1:0;
	lcd.bit.DB4=(cmd & 0X01)?1:0;
	enableBit(lcd.octet);

	while(isBusy());
}
     
void ADA772::data(uint8_t dat)
{
	ST_LCD lcd;

	lcd.octet = 0;
	lcd.bit.BACKLIGHT = _backlight;
	lcd.bit.DB7=(dat & 0X80)?1:0;
	lcd.bit.DB6=(dat & 0X40)?1:0;
	lcd.bit.DB5=(dat & 0X20)?1:0;
	lcd.bit.DB4=(dat & 0X10)?1:0;
	lcd.bit.RS=1;
	enableBit(lcd.octet);

	while(isBusy());

	lcd.octet = 0;
	lcd.bit.BACKLIGHT = _backlight;
	lcd.bit.DB7=(dat & 0X08)?1:0;
	lcd.bit.DB6=(dat & 0X04)?1:0;
	lcd.bit.DB5=(dat & 0X02)?1:0;
	lcd.bit.DB4=(dat & 0X01)?1:0;
	lcd.bit.RS=1;
	enableBit(lcd.octet);

	while(isBusy());
}

void ADA772::enableBit(uint8_t octet)
{
	ST_LCD lcd;
	lcd.octet = octet;

	// ecriture des donnees
	lcd.bit.EN=0;
	_pia->set(1, lcd.octet);
	Tempo::millisecondes(1);

	// debut validation des donnees
	lcd.bit.EN=1;
	_pia->set(1, lcd.octet);
	Tempo::millisecondes(1);

	// fin validation des donnees
	lcd.bit.EN=0;
	_pia->set(1, lcd.octet);
	Tempo::millisecondes(1);
}

bool ADA772::isBusy(uint8_t *addressCounter)
{
	uint8_t octet = readCmd();
	if (addressCounter) *addressCounter = octet & 0x7F;
	return ((octet & 0x80) >> 7);
}

uint8_t ADA772::readData()
{
	ST_LCD lcd;
	lcd.octet = 0;

	lcd.bit.BACKLIGHT = _backlight;
	lcd.bit.RW_ = 1;
	lcd.bit.RS  = 1;
	lcd.bit.EN  = 0;
	_pia->set(1, lcd.octet);

	uint8_t octet = _pia->get(1) & 0xF0;
	octet |= (_pia->get(1) & 0xF0) >> 4;
	return octet;
}

uint8_t ADA772::readCmd()
{
	ST_LCD lcd;
	lcd.octet = 0;

	lcd.bit.BACKLIGHT = _backlight;
	lcd.bit.RW_ = 1;
	lcd.bit.RS  = 0;
	lcd.bit.EN  = 0;
	_pia->set(1, lcd.octet);

	uint8_t octet = _pia->get(1) & 0xF0;
	octet |= (_pia->get(1) & 0xF0) >> 4;
	return octet;
}

void ADA772::write (uint8_t cmd, uint8_t rs, uint8_t rw_)
{
	ST_LCD lcd;
	lcd.octet = 0;
	lcd.bit.DB7=(cmd & 0X8)?1:0;
	lcd.bit.DB6=(cmd & 0X4)?1:0;
	lcd.bit.DB5=(cmd & 0X2)?1:0;
	lcd.bit.DB4=(cmd & 0X1)?1:0;
	lcd.bit.RW_ = rw_;
	lcd.bit.RS  = rs;
	lcd.bit.EN  = 0;
	enableBit(lcd.octet);
}

