#include "modbusmsgheader.h"
#include "modbusmsgexception.h"
#include "log.h"
#include <sstream>

Modbus::ModbusMsgHeader::ModbusMsgHeader(uint8_t fct_code)
: _error_code(0)
, _slave_address(0xF8)
, _function_code(fct_code)
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

void Modbus::ModbusMsgHeader::setSlaveAddress(uint8_t addr)
{
	_slave_address = addr;
}

uint8_t Modbus::ModbusMsgHeader::slaveAddress() const
{
	return _slave_address;
}

uint32_t Modbus::ModbusMsgHeader::decodeHeader()
{
	uint32_t cpt = 0;

	_buffer_in.read(&_slave_address, 1, cpt);
	cpt += 1;

	uint8_t t;
	_buffer_in.read(&t, 1, cpt);
	_function_code = t & 0x7F;
	_error_code = t & 0x80;
	cpt += 1;

	if (_error_code)
	{
		uint8_t code_erreur;
		_buffer_in.read(&code_erreur, 1, cpt);
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

uint32_t Modbus::ModbusMsgHeader::encodeHeader()
{
	uint32_t cpt = 0;

	_buffer_out.write(&_slave_address, 1, cpt);
	cpt += 1;

	uint8_t t = (_function_code & 0x7F) | ((_error_code) ? 0x80 : 0);
	_buffer_out.write(&t, 1, cpt);
	cpt += 1;

	return cpt;
}
