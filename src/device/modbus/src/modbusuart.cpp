#include "modbusuart.h"
#include <termios.h>
#include <unistd.h>
#include "rs232exception.h"

Modbus::ModbusUart::ModbusUart(const std::string & device_p)
: RS232(device_p)
{}

Modbus::ModbusUart::~ModbusUart()
{}
