#include "n4dih32.h"

#include "modbusrtu.h"
#include "modbusmsgdirect.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include <thread>

Modbus::N4DIH32::N4DIH32(uint8_t addr_slave, Modbus::ModbusRtu * rtu)
: _rtu(rtu)
, _module_address(addr_slave)
{}

Modbus::N4DIH32::~N4DIH32()
{}

void Modbus::N4DIH32::get()
{
	Modbus::ModbusMsgFC03 msg(0x0080, 0x010);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::N4DIH32::getAll()
{
	Modbus::ModbusMsgFC03 msg(0x00C0, 0x002);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::N4DIH32::setTempoAutomaticReporting(uint8_t secondes)
{
	Modbus::ModbusMsgFC06 msg(0x00FD);
	msg.set(secondes);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::N4DIH32::setAllAutomaticReporting(uint8_t all_input)
{
	Modbus::ModbusMsgFC06 msg(0x00FE);
	msg.set(all_input);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::N4DIH32::baudRate()
{
	Modbus::ModbusMsgFC03 msg(0x00FF, 1);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::N4DIH32::setBaudRate(uint16_t br)
{
	Modbus::ModbusMsgFC06 msg(0x00FF);
	msg.set(br);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::N4DIH32::resetFactory()
{
	Modbus::ModbusMsgFC06 msg(0x00FF);
	msg.set(0x0005);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}
