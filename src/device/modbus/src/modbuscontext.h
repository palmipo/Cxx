#ifndef MODBUS_CONTEXT_H
#define MODBUS_CONTEXT_H

#include <streambuf>

namespace Modbus
{
    class ModbusContext : public std::streambuf
    {
        public:
            ModbusContext();
            virtual ~ModbusContext();
			
			// virtual int length() const;
    };
}

#endif
