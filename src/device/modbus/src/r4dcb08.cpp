Modbus::R4DCB08::R4DCB08(ModbusRtu * rtu)
{
}

Modbus::R4DCB08::~R4DCB08()
{
}

int16_t Modbus::R4DCB08::temperature(int8_t sonde)
{
	ModbusMsgFC03 msg;
	rtu->write(&msg);
	rtu->read(&msg);
}

int16_t Modbus::R4DCB08::temperatureCorrectionValue(int8_t sonde)
{
	ModbusMsgFC03 msg;
	rtu->write(&msg);
	rtu->read(&msg);
}

int16_t Modbus::R4DCB08::automaticTemperatureReport(int8_t sonde)
{
	ModbusMsgFC03 msg;
	rtu->write(&msg);
	rtu->read(&msg);
}
