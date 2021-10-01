#ifndef MODBUS_MSG_FC16_H
#define MODBUS_MSG_FC16_H

#include "modbusmsgheader.h"
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
	class MODBUS_DLL ModbusMsgFC16 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC16();
			virtual ~ModbusMsgFC16();

			// question
			virtual void setRegister(uint16_t, uint16_t);

			// constitution message
			virtual uint16_t encodeQuestion();
			virtual uint16_t decodeQuestion();
			virtual uint16_t decodeResponse();

		protected:
			std::map < uint16_t, uint16_t > registers;
	};
}

#endif
