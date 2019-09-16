#ifndef MODBUSRTUMSGERROR_H
#define MODBUSRTUMSGERROR_H

#include "modbusrtumsg.h"

namespace Modbus
{
	class ModbusRtuMsgError : public ModbusRtuMsg
	{
		public:
			ModbusRtuMsgError(RS232 * rtu)
			: ModbusRtuMsg(rtu)
			{}

			virtual ~ModbusRtuMsgError()
			{}
			
			virtual s32 decode(u8*, s32);
	};
}

s32 Modbus::ModbusRtuMsgError::decode(u8* msg, s32 len)
{
	s32 cpt = 2;
	cpt += recvDirectly(msg+cpt, 1);

	return cpt;
}

#endif
	