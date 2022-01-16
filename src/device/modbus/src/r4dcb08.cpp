#include "r4dcb08.h"
#include "modbusrtu.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include <thread>

Modbus::R4DCB08::R4DCB08(ModbusRtu * rtu)
: _rtu(rtu)
{
}

Modbus::R4DCB08::~R4DCB08()
{
}

int16_t Modbus::R4DCB08::temperature(int8_t sonde)
{
	ModbusMsgFC03 msg(sonde, 1);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);

	return msg.get(sonde);
}

int16_t Modbus::R4DCB08::temperatureCorrectionValue(int8_t sonde)
{
	ModbusMsgFC03 msg(sonde+1, 1);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);

	return msg.get(sonde+1);
}

void Modbus::R4DCB08::setTemperatureCorrectionValue(uint16_t sonde, uint16_t value)
{
	ModbusMsgFC06 msg(sonde+1);
	msg.set(value);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);
}

int16_t Modbus::R4DCB08::automaticTemperatureReport()
{
	ModbusMsgFC03 msg(0x00FD, 1);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);

	return msg.get(0x00FD);
}

void Modbus::R4DCB08::setAutomaticTemperatureReport(int16_t tempo)
{
	ModbusMsgFC06 msg(0x00FD);
	msg.set(tempo);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);
}

int16_t Modbus::R4DCB08::moduleAddress()
{
	ModbusMsgFC03 msg(0x00FE, 1);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);

	return msg.get(0x00FE);
}

void Modbus::R4DCB08::setModuleAddress(uint16_t addr)
{
	ModbusMsgFC06 msg(0x00FE);
	msg.set(addr);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);
}

int16_t Modbus::R4DCB08::baudRate()
{
	ModbusMsgFC03 msg(0x00FF, 1);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);

	return msg.get(0x00FF);
}

void Modbus::R4DCB08::setBaudRate(uint16_t br)
{
	ModbusMsgFC06 msg(0x00FF);
	msg.set(br);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	_rtu->read(&msg);
}
