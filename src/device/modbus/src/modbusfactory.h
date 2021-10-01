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

class ModbusChannel;
namespace Modbus
{
	class ModbusChannel;
	class MODBUS_DLL ModbusFactory : public PollFactory
	{
		public:
			ModbusFactory();
			virtual ~ModbusFactory();

			virtual ModbusChannel * get(const std::string &);
			virtual ModbusChannel * tcp(const std::string &);
			virtual ModbusChannel * rtu(const std::string &, int32_t=19200, int32_t=1, int32_t=1);
			virtual void close(const std::string &);

			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();

		protected:
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);

		protected:
			std::map<std::string, ModbusChannel * > _codec;
	};
}

#endif /* MODBUS_FACTORY_H */
