#ifndef MODBUS_UART_H
#define MODBUS_UART_H

#include "rs232.h"

namespace Modbus
{
	class ModbusUart : public RS232
	{
		public:
			ModbusUart(const std::string &);
			virtual ~ModbusUart();
	};
}

#endif
