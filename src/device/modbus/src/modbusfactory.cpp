#include "modbusfactory.h"
#include "modbustcp.h"
#include "modbusrtu.h"
#include "modbusexception.h"
#include "sockettcp.h"
#include "socketexception.h"
#include "rs232.h"
#include "rs232exception.h"
#include "log.h"
#include <sstream>

// MODBUS Driver 27700
// #define TCP_PORT 27700

// MODBUS over TCP/IP
#define TCP_PORT 502

Modbus::ModbusFactory::ModbusFactory()
{}

Modbus::ModbusFactory::~ModbusFactory()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~ModbusFactory");

	std::map<std::string, ModbusChannel *>::iterator it = _codec.begin();
	while (it != _codec.end())
	{
		delete it->second; it->second = 0;
		it++;
	}
}

Modbus::ModbusChannel * Modbus::ModbusFactory::get(const std::string & host)
{
    std::map<std::string, ModbusChannel *>::iterator it = _codec.find(host);
    if (it != _codec.end())
    {
        return it->second;
    }

    throw Modbus::ModbusException(__FILE__, __LINE__, "i can't get enough");
}

Modbus::ModbusChannel * Modbus::ModbusFactory::tcp(Socket::SocketTcp * tcp, int8_t id_slave)
{
    // recherche de l'existant
    try
    {
        Modbus::ModbusChannel * res = get(tcp);
        return res;
    }
    catch(...)
    {}

    // 
    Modbus::ModbusTcp * modbus_tcp = new Modbus::ModbusTcp(tcp);
    if (modbus_tcp)
    {
		_codec[host] = modbus_tcp;
    }

    return modbus_tcp;
}

Modbus::ModbusChannel * Modbus::ModbusFactory::rtu(RS232 * serial)
{
    try
    {
        Modbus::ModbusChannel * res = get(serial);
        return res;
    }
    catch(...)
    {}

    Modbus::ModbusRtu * modbus_rtu = new Modbus::ModbusRtu(serial);
    if (modbus_rtu)
    {
	_codec[device] = modbus_rtu;
    }

    return modbus_rtu;
}

void Modbus::ModbusFactory::close(const std::string & host)
{
    std::map<std::string, ModbusChannel *>::iterator it = _codec.find(host);
    if (it != _codec.end())
    {
        delete it->second;
	_codec.erase(it);
    }
}

