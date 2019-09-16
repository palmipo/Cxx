#ifndef MODBUS_MSG_FC08_H
#define MODBUS_MSG_FC08_H

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
	class MODBUS_DLL ModbusMsgFC08 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC08()
			: ModbusMsgHeader(0x08)
			, data_length(0)
			{}

			virtual ~ModbusMsgFC08()
			{}
			
			virtual void ReturnQueryData(uint8_t*, uint16_t);
			virtual void RestartCommunicationsOption();
			virtual void ReturnDiagnosticRegister();
			virtual void ChangeASCIIInputDelimiter();
			virtual void ForceListenOnlyMode();
			virtual void ClearCountersAndDiagnosticRegister();
			virtual void ReturnBusMessageCount();
			virtual void ReturnBusCommunicationErrorCount();
			virtual void ReturnBusExceptionErrorCount();
			virtual void ReturnSlaveMessageCount();
			virtual void ReturnSlaveNoResponseCount();
			virtual void ReturnSlaveNAKCount();
			virtual void ReturnSlaveBusyCount();
			virtual void ReturnBusCharacterOverrunCount();
			virtual void ClearOverrunCounterAndFlag();

			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);
		
		protected:
			uint16_t subfunction;
			uint16_t data[128];
			uint16_t data_length;
	};
}

#endif
