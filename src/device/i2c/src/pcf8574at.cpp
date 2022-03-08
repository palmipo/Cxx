#include "pcf8574at.h"

PCF8574AT::PCF8574AT(uint8_t address, CtrlI2C * i2c)
: PCF8574A(0x3F | (address & 0x7), i2c)
{}
