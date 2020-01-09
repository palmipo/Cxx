#ifndef MODBUS_MSG_FC43_H
#define MODBUS_MSG_FC43_H

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
	class ModbusMsgFC43Object
	{
		public:
			ModbusMsgFC43Object()
			{}

			virtual ~ModbusMsgFC43Object()
			{}

			uint8_t object_id;
			uint8_t object_value[256];
			uint16_t object_length;
	};

	class MODBUS_DLL ModbusMsgFC43 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC43()
			: ModbusMsgHeader(0x2B)
			{}

			virtual ~ModbusMsgFC43()
			{}

			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);
		
		protected:
			uint8_t mei_type;
			uint8_t device_id;
			uint8_t object_id;

			uint8_t conformity_level;
			uint8_t more_follow;
			uint8_t next_object_id;
			uint8_t nb_object;

			ModbusMsgFC43Object object[256];
	};
}

#endif
