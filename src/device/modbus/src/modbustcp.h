#ifndef MODBUS_TCP_H
#define MODBUS_TCP_H

#include "modbuschannel.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
	#ifdef MAKE_MODBUS_DLL
		#define MODBUS_DLL __declspec(dllexport)
	#else
		#define MODBUS_DLL __declspec(dllimport)
	#endif
#else
	#define MODBUS_DLL
#endif

class PollDevice;
namespace Modbus
{
	class ModbusMsg;
	class MODBUS_DLL ModbusTcp : public ModbusChannel
	{
        public:
			ModbusTcp(PollDevice *);
			virtual ~ModbusTcp();

		protected:
			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();

        protected:
			uint16_t _transaction_id;
			uint16_t _protocol_id;
	};
}

#endif /* MODBUSPDU_H */
