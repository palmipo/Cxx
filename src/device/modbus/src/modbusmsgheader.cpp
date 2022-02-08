#include "modbusmsgheader.h"
#include "modbusmsgexception.h"
#include "log.h"
#include <sstream>

Modbus::ModbusMsgHeader::ModbusMsgHeader(uint8_t fct_code)
: ModbusMsg(fct_code)
, _error_code(0)
{}

Modbus::ModbusMsgHeader::~ModbusMsgHeader()
{}

uint8_t Modbus::ModbusMsgHeader::functionCode() const
{
	return _function_code;
}

uint8_t Modbus::ModbusMsgHeader::errorCode() const
{
	return _error_code;
}

int32_t Modbus::ModbusMsgHeader::write(uint8_t * data, int32_t length)
{
	if (_function_code != data[0] & 0x7F)
	{
		throw ModbusMsgException(__FILE__, __LINE__, "reception d'un message incoherent");
	}

	int32_t cpt = 0;

	_function_code = data[cpt] & 0x7F;
	_error_code = data[cpt] & 0x80;
	cpt += 1;

	if (_error_code)
	{
		uint8_t code_erreur = data[cpt];
		cpt+=1;

		std::string msg;
		switch(code_erreur)
		{
			case 0x01:
				msg = "Illegal Function";
				break;

			case 0x02:
				msg = "Illegal Data Address";
				break;

			case 0x03:
				msg = "Illegal Data Value";
				break;

			case 0x04:
				msg = "Slave Device Failure";
				break;

			case 0x05:
				msg = "Acknowledge";
				break;

			case 0x06:
				msg = "Slave Device Busy";
				break;

			case 0x07:
				msg = "Negative Acknowledge";
				break;

			case 0x08:
				msg = "Memory Parity Error";
				break;

			case 0x0A:
				msg = "Gateway Path Unavailable";
				break;

			case 0x0B:
				msg = "Gateway Target Device Failed to Respond";
				break;
				
			default:
				msg = "Erreur inconnue ...";
				break;
		}
		
		throw ModbusMsgException(__FILE__, __LINE__, msg);
	}

	return cpt;
}

int32_t Modbus::ModbusMsgHeader::read(uint8_t * data, int32_t length)
{
	uint32_t cpt = 0;

	data[cpt] = _function_code;
	cpt += 1;

	return cpt;
}
