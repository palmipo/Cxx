#include "modbusmsgfc08.h"
#include "modbuschannel.h"
#include <iostream>
#include <iomanip>
#include <cstring>

// 00  Return Query Data 
void Modbus::ModbusMsgFC08::ReturnQueryData(uint8_t * buffer, uint16_t len)
{
	subfunction = 0x00;
	data_length = len;
	::memcpy(data, buffer, len);
}

// 01  Restart Communications Option 
void Modbus::ModbusMsgFC08::RestartCommunicationsOption()
{
	subfunction = 0x01;
}

// 02  Return Diagnostic Register 
void Modbus::ModbusMsgFC08::ReturnDiagnosticRegister()
{
	subfunction = 0x02;
}

// 03  Change ASCII Input Delimiter 
void Modbus::ModbusMsgFC08::ChangeASCIIInputDelimiter()
{
	subfunction = 0x03;
}

// 04  Force Listen Only Mode 
void Modbus::ModbusMsgFC08::ForceListenOnlyMode()
{
	subfunction = 0x04;
}

// 0A  Clear Counters and Diagnostic Register 
void Modbus::ModbusMsgFC08::ClearCountersAndDiagnosticRegister()
{
	subfunction = 0x0a;
}

// 0B  Return Bus Message Count 
void Modbus::ModbusMsgFC08::ReturnBusMessageCount()
{
	subfunction = 0x0b;
}

// 0C  Return Bus Communication Error Count 
void Modbus::ModbusMsgFC08::ReturnBusCommunicationErrorCount()
{
	subfunction = 0x0c;
}

// 0D  Return Bus Exception Error Count 
void Modbus::ModbusMsgFC08::ReturnBusExceptionErrorCount()
{
	subfunction = 0x0d;
}

// 0E  Return Slave Message Count 
void Modbus::ModbusMsgFC08::ReturnSlaveMessageCount()
{
	subfunction = 0x0e;
}

// 0F  Return Slave No Response Count 
void Modbus::ModbusMsgFC08::ReturnSlaveNoResponseCount()
{
	subfunction = 0x0f;
}

// 10  Return Slave NAK Count 
void Modbus::ModbusMsgFC08::ReturnSlaveNAKCount()
{
	subfunction = 0x10;
}

// 11  Return Slave Busy Count 
void Modbus::ModbusMsgFC08::ReturnSlaveBusyCount()
{
	subfunction = 0x11;
}

// 12  Return Bus Character Overrun Count 
void Modbus::ModbusMsgFC08::ReturnBusCharacterOverrunCount()
{
	subfunction = 0x12;
}

// 14  Clear Overrun Counter and Flag
void Modbus::ModbusMsgFC08::ClearOverrunCounterAndFlag()
{
	subfunction = 0x14;
}

uint16_t Modbus::ModbusMsgFC08::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

	data[cpt] = (subfunction & 0xFF00) >> 8; ++cpt;
	data[cpt] = subfunction & 0x00FF; ++cpt;
	
	uint16_t i=0;
	while (i < data_length)
	{
		data[cpt] = (data[i] & 0xFF00) >> 8; ++cpt;
		data[cpt] = data[i] & 0x00FF; ++cpt;
		i += 1;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC08::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	subfunction = data[cpt] << 8; ++cpt;
	subfunction |= data[cpt]; ++cpt;
	
	data_length = 0;
	while (cpt < len)
	{
		data[data_length] = data[cpt] << 8; ++cpt;
		data[data_length] |= data[cpt]; ++cpt;
		data_length += 1;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC08::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		subfunction = data[cpt] << 8; cpt += 1;
		subfunction |= data[cpt]; cpt += 1;

		uint16_t i=0;
		while (i < data_length)
		{
			data[i] = data[cpt] << 8; ++cpt;
			data[i] |= data[cpt]; ++cpt;
			i += 1;
		}
	}

	return cpt;
}
