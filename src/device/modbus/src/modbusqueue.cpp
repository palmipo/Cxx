#include "modbusqueue.h"
#include "modbusmsg.h"
#include "log.h"
#include <sstream>

Modbus::ModbusQueue::ModbusQueue()
{}

Modbus::ModbusQueue::~ModbusQueue()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~ModbusQueue");

	std::map < std::pair < uint8_t, uint8_t > , std::queue < ModbusMsg * > >::iterator it = _fifo.begin();
	while (it != _fifo.end())
	{
		std::queue < ModbusMsg * > q = it->second;
		while (!q.empty())
		{
			Modbus::ModbusMsg * m = q.front();
			q.pop();
			delete m;
		}
		it++;
	}
}

int32_t Modbus::ModbusQueue::isEmpty(uint8_t slave_address, uint8_t function_code)
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "isEmpty");

	std::map < std::pair < uint8_t, uint8_t > , std::queue < ModbusMsg * > >::iterator it = _fifo.find(std::make_pair(slave_address, function_code));
	if (it != _fifo.end())
	{
		//~ Log::getLogger()->debug(__FILE__, __LINE__, "trouver");
		return it->second.empty();
	}
	
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "pas trouver");
	return 1;
}

Modbus::ModbusMsg * Modbus::ModbusQueue::get(uint8_t slave_address, uint8_t function_code)
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "get");

	std::map < std::pair < uint8_t, uint8_t > , std::queue < ModbusMsg * > >::iterator it = _fifo.find(std::make_pair(slave_address, function_code));
	if (it != _fifo.end())
	{
		ModbusMsg * msg = it->second.front();
		it->second.pop();
		return msg;
	}
	
	return 0;
}

void Modbus::ModbusQueue::add(uint8_t slave_address, uint8_t function_code, Modbus::ModbusMsg * msg)
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "add");
	//~ std::stringstream ss;
	//~ ss << (int32_t)slave_address << " " << (int32_t)function_code;
	//~ Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	std::map < std::pair < uint8_t, uint8_t > , std::queue < ModbusMsg * > >::iterator it = _fifo.find(std::make_pair(slave_address, function_code));
	if (it != _fifo.end())
	{
		it->second.push(msg);
	}
	else
	{
		std::queue < ModbusMsg * > q;
		q.push(msg);
		_fifo[std::make_pair(slave_address, function_code)] = q;
	}
	//~ Log::getLogger()->debug(__FILE__, __LINE__, std::to_string(_fifo.size()));
}
