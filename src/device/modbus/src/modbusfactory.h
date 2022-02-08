#ifndef MODBUS_FACTORY_H
#define MODBUS_FACTORY_H

#include "pollfactory.h"
#include <string>
#include <map>

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
	class ModbusChannel;
	class MODBUS_DLL ModbusFactory : public PollFactory
	{
		public:
			ModbusFactory();
			virtual ~ModbusFactory();

			virtual ModbusChannel * get(const std::string &);
			virtual ModbusChannel * tcp(const std::string &, int8_t = 1);
			virtual ModbusChannel * rtu(const std::string &, int32_t = 9600, int32_t = 8, int32_t = 'N', int32_t = 1);
			virtual void close(const std::string &);

		protected:
			std::map<std::string, ModbusChannel * > _codec;
	};
}

#endif /* MODBUS_FACTORY_H */
