#include "r4d3b16.h"
#include "modbusrtu.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include "modbusmsgdirect.h"
#include "log.h"

#include <thread>

Modbus::R4D3B16::R4D3B16(uint8_t addr_slave, Modbus::ModbusRtu *rtu)
: _rtu(rtu)
, _module_address(addr_slave)
{}

Modbus::R4D3B16::~R4D3B16()
{}

void Modbus::R4D3B16::open(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0100);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}

void Modbus::R4D3B16::close(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0200);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}

void Modbus::R4D3B16::toggle(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0300);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}

void Modbus::R4D3B16::get(uint16_t coils)
{
	ModbusMsgFC03 msg(coils, 0x0001);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}

void Modbus::R4D3B16::getAll()
{
	ModbusMsgFC03 msg(0x0001, 0x0010);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}

void Modbus::R4D3B16::openAll()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "openAll()");

	ModbusMsgFC06 msg(0x0000);
	msg.set(0x0700);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}

void Modbus::R4D3B16::closeAll()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "closeAll()");

	ModbusMsgFC06 msg(0x0000);
	msg.set(0x0800);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	_rtu->read(&msg);
}
