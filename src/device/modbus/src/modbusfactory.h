#ifndef MODBUS_FACTORY_H
#define MODBUS_FACTORY_H

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
	class MODBUS_DLL ModbusFactory
	{
		public:
			ModbusFactory();
			virtual ~ModbusFactory();

			virtual ModbusChannel * get(const std::string &);
			virtual ModbusChannel * tcp(Socket::SocketBase *);
			virtual ModbusChannel * rtu(RS232 *);
			virtual void close(const std::string &);

		protected:
			std::map<std::string, ModbusChannel * > _codec;
	};
}

#endif /* MODBUS_FACTORY_H */
