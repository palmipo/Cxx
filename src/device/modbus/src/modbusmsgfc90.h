#ifndef MODBUS_MSG_FC90_H
#define MODBUS_MSG_FC90_H

#include "modbusmsgheader.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
	#ifdef MAKE_MODBUS_DLL
		#define MODBUS_DLL __declspec(dllexport)
	#else
		#define MODBUS_DLL __declspec(dllimport)
	#endif
#else
	#define MODBUS_DLL
#endif

namespace Modbus
{
	class ModbusMsgFC90 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC90()
			: ModbusMsgHeader(0x5A)
			{}
            
			virtual ~ModbusMsgFC90()
			{}
	};
}

#endif
