#ifndef MODBUS_EXCEPTION_H
#define MODBUS_EXCEPTION_H

#include "pollexception.h"

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
	class MODBUS_DLL ModbusException : public PollException
	{
		public:
			ModbusException(const std::string & fichier, int32_t ligne, int32_t numerror)
			: PollException(fichier, ligne, numerror)
			{}

			ModbusException(const std::string & fichier, int32_t ligne, const std::string & error)
			: PollException(fichier, ligne, error)
			{}
	};
}

#endif /* MODBUS_EXCEPTION_H */
