#include "modbuseasy.h"
#include "modbusfactory.h"
#include "modbustcp.h"
#include "modbusrtu.h"
#include "modbusexception.h"
#include "modbusmsgfc01.h"
#include "modbusmsgfc02.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc04.h"
#include "modbusmsgfc05.h"
#include "modbusmsgfc06.h"
#include "modbusmsgfc08.h"
#include "modbusmsgfc11.h"
#include "modbusmsgfc15.h"
#include "modbusmsgfc16.h"
#include "modbusmsgfc23.h"
#include "modbusmsgfc43.h"
#include "modbusmsgfc71.h"
#include "modbusmsgfc90.h"
#include <iostream>
#include <sstream>

Modbus::ModbusEasy::ModbusEasy(ModbusFactory * factory)
: _factory(factory)
, total_timeout(10000)
{}

Modbus::ModbusEasy::~ModbusEasy()
{}

void Modbus::ModbusEasy::tcp(const std::string & type, const std::string & host)
{
	// std::cout << __FILE__ << __LINE__ << std::endl;

	_factory->tcp(host);
}

void Modbus::ModbusEasy::rtu(const std::string & type, const std::string & host, s32 baudrate, s32 stopbits, s32 parity)
{
	// std::cout << __FILE__ << __LINE__ << std::endl;
	_rtu_host = host;
	_factory->rtu(host, baudrate, stopbits, parity);
}

void Modbus::ModbusEasy::close(const std::string & device, const std::string & host)
{
	// std::cout << __FILE__ << __LINE__ << std::endl;

	_factory->close(host);
}

void Modbus::ModbusEasy::close(const std::string & host)
{
	// std::cout << __FILE__ << __LINE__ << std::endl;

	_factory->close(host);
}

void Modbus::ModbusEasy::closeAll()
{
	// std::cout << __FILE__ << __LINE__ << std::endl;

	_factory->closeAll();
}

void Modbus::ModbusEasy::setReadIntervalTimeout(const std::string & device, s32 timeout)
{
	std::string host = device;
	if (device == "SER")
	{
		host = _rtu_host;
	}

	_factory->get(host)->setInterCharacterTimer(timeout);
}

void Modbus::ModbusEasy::setReadTotalTimeout(const std::string & device, s32 timeout)
{
	total_timeout = timeout;
}

s32 Modbus::ModbusEasy::getReadIntervalTimeout(const std::string & device)
{
	std::string host = device;
	if (device == "SER")
	{
		host = _rtu_host;
	}

	return _factory->get(host)->getInterCharacterTimer();
}

s32 Modbus::ModbusEasy::getReadTotalTimeout(const std::string & device)
{
	return total_timeout;
}

u16 Modbus::ModbusEasy::FC01(const std::string & device, u8 slave_address, u16 data_addr, u16 total_data, u16 total_response, u8 * response)
{
	// std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
	if (device == "SER")
	{
		host = _rtu_host;
	}

	ModbusMsgFC01 msg;
	msg.setSlaveAddress(slave_address);
	msg.readCoilStatus(data_addr, total_data);
	_factory->get(host)->sendFC(&msg);

	if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}

	return total_response;
}

u16 Modbus::ModbusEasy::FC02(const std::string & device, u8 slave_address, u16 data_addr, u16 total_data, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	ModbusMsgFC02 msg;
	msg.setSlaveAddress(slave_address);
	msg.readInputStatus(data_addr, total_data);
	_factory->get(host)->sendFC(&msg);

	if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::FC03(const std::string & device, u8 slave_address, u16 data_addr, u16 total_data, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }
	
	ModbusMsgFC03 msg;
	msg.setSlaveAddress(slave_address);
	msg.setRegisterAddr(data_addr, total_data);
	_factory->get(host)->sendFC(&msg);
    if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::FC04(const std::string & device, u8 slave_address, u16 data_addr, u16 total_data, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	ModbusMsgFC04 msg;
	msg.setSlaveAddress(slave_address);
	_factory->get(host)->sendFC(&msg);
    if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::FC05(const std::string & device, u8 slave_address, u16 data_addr, u16 value, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	ModbusMsgFC05 msg;
	msg.setSlaveAddress(slave_address);
	_factory->get(host)->sendFC(&msg);
    if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::FC06(const std::string & device, u8 slave_address, u16 data_addr, u16 data, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	ModbusMsgFC06 msg;
	msg.setSlaveAddress(slave_address);
	msg.setRegister(data_addr, data);
	_factory->get(host)->sendFC(&msg);
    if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::FC15(const std::string & device, u8 slave_address, u16 data_addr, u16 total_data, u8 * data, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	ModbusMsgFC15 msg;
	msg.setSlaveAddress(slave_address);
	_factory->get(host)->sendFC(&msg);
    if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::FC16(const std::string & device, u8 slave_address, u16 data_addr, u16 total_data, u16 * data, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	ModbusMsgFC16 msg;
	msg.setSlaveAddress(slave_address);
	for (u16 i=0; i<total_data; ++i)
	{
		msg.setRegister(data_addr+i, data[i]);
	}
	_factory->get(host)->sendFC(&msg);
    if (_factory->scrute(total_timeout) > 0)
	{
		_factory->get(host)->receiveDirect(response, total_response);
	}
    
    return 0;
}

u16 Modbus::ModbusEasy::direct(const std::string & device, u8 * data, u16 nb_data, s32 calcul_crc, u16 total_response, u8 * response)
{
    // std::cout << __FILE__ << __LINE__ << std::endl;

	std::string host = device;
    if (device == "SER")
    {
        host = _rtu_host;
    }

	_factory->get(host)->sendDirect(data, nb_data, calcul_crc);
    if (_factory->scrute(total_timeout) > 0)
	{
		return _factory->get(host)->receiveDirect(response, total_response);
	}

    return 0;
}
