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
			virtual ~ModbusMsgDirect();

			virtual uint16_t msgSendLength() const;
			virtual uint16_t msgReceiveLength() const;

			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t encodeResponse(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);

		protected:
			uint8_t _msg_snd[512];
			uint16_t _msg_snd_len;
			uint8_t _msg_rcv[512];
			uint16_t _msg_rcv_len;
	};
}

#endif
