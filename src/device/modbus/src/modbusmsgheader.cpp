#include "modbusmsgheader.h"
#include "modbusmsgexception.h"
#include "codec.h"
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
Codec codec;
uint8_t fct_code = 0;
codec.encoder_decoder(&fct_code, 0, data, 0, 7);
codec.encoder_decoder(&_error_code, 0, data, 7, 1);
	if (_function_code != fct_code)
	{
		throw ModbusMsgException(__FILE__, __LINE__, "reception d'un message incoherent");
	}

uint8_t cpt = 1;

	if (_error_code)
	{
codec.encoder_decoder(&code_erreur, 0, data, 8, 8);
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
	uint32_t cpt = 1;
Codec codec;
codec.encoder_decoder(data, 0, &_function_code, 0, 8);

	return cpt;
}
