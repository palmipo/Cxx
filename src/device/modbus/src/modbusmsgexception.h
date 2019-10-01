#ifndef MODBUS_MSG_EXCEPTION_H
#define MODBUS_MSG_EXCEPTION_H

#include "modbusexception.h"

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
	class ModbusMsgException : public ModbusException
	{
		public:
			ModbusMsgException(const std::string & fichier, int32_t ligne, const std::string & str)
			: ModbusException(fichier, ligne, str)
			{}
	};
}

#endif
