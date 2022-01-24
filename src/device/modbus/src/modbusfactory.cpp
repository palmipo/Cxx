#include "modbusfactory.h"
#include "modbuschannel.h"
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
: PollFactory()
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

Modbus::ModbusChannel * Modbus::ModbusFactory::tcp(const std::string & host, int8_t id_slave)
{
    // recherche de l'existant
    try
    {
        Modbus::ModbusChannel * res = get(host);
        return res;
    }
    catch(...)
    {}
    
    // creation de la socket
    Socket::SocketTcp * tcp = new Socket::SocketTcp();
    if (!tcp)
    {
        throw Modbus::ModbusException(__FILE__, __LINE__, "i can't tcp enough");
    }

    // connexion a device
    tcp->connexion(host, TCP_PORT);
    add(tcp);

    // 
    Modbus::ModbusTcp * modbus_tcp = new Modbus::ModbusTcp(tcp);
    if (modbus_tcp)
    {
		_codec[host] = modbus_tcp;
    }

    return modbus_tcp;
}

Modbus::ModbusChannel * Modbus::ModbusFactory::rtu(const std::string & device, int32_t baudrate, int32_t data, int32_t parity, int32_t stopbits)
{
    try
    {
        Modbus::ModbusChannel * res = get(device);
        return res;
    }
    catch(...)
    {}
    
    RS232 * serial = new RS232(device);
    if (!serial)
    {
        throw Modbus::ModbusException(__FILE__, __LINE__, "i can't rtu enough");
    }

    if ((parity != 'N') && (parity == 'E') && (parity == 'O'))
        throw Modbus::ModbusException(__FILE__, __LINE__, " parity : bad parameters");
    
    speed_t cbaudrate;
    if (baudrate == 1200)
        cbaudrate = B1200;
    else if (baudrate == 2400)
        cbaudrate = B2400;
    else if (baudrate == 4800)
        cbaudrate = B4800;
    else if (baudrate == 9600)
        cbaudrate = B9600;
    else if (baudrate == 19200)
        cbaudrate = B19200;
    else if (baudrate == 38400)
        cbaudrate = B38400;
    else
        throw Modbus::ModbusException(__FILE__, __LINE__, " baud rate : bad parameters");

    serial->setConfig(cbaudrate, data, parity, stopbits);
    serial->setInterCharacterTimer(1);
    add(serial);

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

