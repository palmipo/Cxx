#include "r4d3b16.h"

Modbus::R4D3B16::R4D3B16(ModbusRtu rtu)
{
}

Modbus::R4D3B16::~R4D3B16()
{
}

void Modbus::R4D3B16::open(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0100);

	rtu.write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	rtu.read(&msg);


void Modbus::R4D3B16::close(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0200);

	rtu.write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	rtu.read(&msg);
}

void Modbus::R4D3B16::toggle(uint8_t coils)
{
	ModbusMsgFC06 msg(coils);
	msg.set(0x0300);

	rtu.write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	rtu.read(&msg);

}

uint8_t Modbus::R4D3B16::read(uint8_t coils)
{
	ModbusMsgFC03 msg(0x01, 0x10);
	msg.set(0x0001);

	rtu.write(&msg);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	rtu.read(&msg);

}

