#include "r4dcb08.h"
#include "modbusrtu.h"
#include "modbusmsgdirect.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include <thread>

#define TEMPO 500

Modbus::R4DCB08::R4DCB08(uint8_t id_slave, ModbusRtu * rtu)
: _rtu(rtu)
, _module_address(id_slave)
{}

Modbus::R4DCB08::~R4DCB08()
{}

void Modbus::R4DCB08::temperature(int8_t sonde)
{
	Modbus::ModbusMsgFC03 msg(sonde, 1);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::allTemperature()
{
	Modbus::ModbusMsgFC03 msg(0x0000, 0x0008);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::temperatureCorrectionValue(int8_t sonde)
{
	Modbus::ModbusMsgFC03 msg(sonde+0x0008, 1);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::setTemperatureCorrectionValue(uint16_t sonde, uint16_t value)
{
	Modbus::ModbusMsgFC06 msg(sonde+0x0008);
	msg.set(value);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::automaticTemperatureReport()
{
	Modbus::ModbusMsgFC03 msg(0x00FD, 1);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::setAutomaticTemperatureReport(int16_t tempo)
{
	Modbus::ModbusMsgFC06 msg(0x00FD);
	msg.set(tempo);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::moduleAddress()
{
	Modbus::ModbusMsgFC03 msg(0x00FE, 1);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::setModuleAddress(uint16_t addr)
{
	Modbus::ModbusMsgFC06 msg(0x00FE);
	msg.set(addr);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::baudRate()
{
	Modbus::ModbusMsgFC03 msg(0x00FF, 1);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::setBaudRate(uint16_t br)
{
	Modbus::ModbusMsgFC06 msg(0x00FF);
	msg.set(br);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}

void Modbus::R4DCB08::resertFactory() const
{
	Modbus::ModbusMsgFC06 msg(0x00FF);
	msg.set(0x0005);

	_rtu->set_id_slave(_module_address);
	_rtu->write(&msg);
}
