#include "r4d3b16.h"
#include "modbusrtu.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include "modbusmsgdirect.h"

#include <thread>

Modbus::R4D3B16::R4D3B16(Modbus::ModbusRtu *rtu)
: _rtu(rtu)
{
}

Modbus::R4D3B16::~R4D3B16()
{
}

void Modbus::R4D3B16::open(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0100);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModbusMsgDirect poubelle;
	_rtu->readDirect(&poubelle);
}

void Modbus::R4D3B16::close(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0200);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModbusMsgDirect poubelle;
	_rtu->readDirect(&poubelle);
}

void Modbus::R4D3B16::toggle(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0300);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModbusMsgDirect poubelle;
	_rtu->readDirect(&poubelle);
}

uint16_t Modbus::R4D3B16::read(uint16_t coils)
{
	ModbusMsgFC03 msg(coils, 0x0001);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModbusMsgDirect poubelle;
	_rtu->readDirect(&poubelle);

	return msg.get(coils);
}

void Modbus::R4D3B16::openAll()
{
	ModbusMsgFC06 msg(0x0000);
	msg.set(0x0700);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModbusMsgDirect poubelle;
	_rtu->readDirect(&poubelle);
}

void Modbus::R4D3B16::closeAll()
{
	ModbusMsgFC06 msg(0x0000);
	msg.set(0x0800);

	_rtu->write(&msg);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModbusMsgDirect poubelle;
	_rtu->readDirect(&poubelle);
}

