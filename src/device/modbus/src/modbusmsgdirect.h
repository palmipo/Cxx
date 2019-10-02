#ifndef MODBUS_MSG_DIRECT_H
#define MODBUS_MSG_DIRECT_H

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
	class MODBUS_DLL ModbusMsgDirect : public ModbusMsgHeader
	{
		public:
			ModbusMsgDirect();
	};
}

#endif
