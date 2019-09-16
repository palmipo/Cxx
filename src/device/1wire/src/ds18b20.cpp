#include "ds18b20.h"
#include "onewire.h"

DS18B20::DS18B20(OneWire * ctrl)
: _ctrl(ctrl)
{}

DS18B20::~DS18B20()
{}

float DS18B20::temperature(u8 num_rom)
{
	float tempe = 0.;
	u8 cmd = 0x44;
	_ctrl->write(num_rom, &cmd, 1);

	cmd = 0xbe;
	u8 t[9];
	_ctrl->read(num_rom, &cmd, 1, t, 9);
	tempe = ((t[1] << 8) + t[0]) * 0.0625;
	
	return tempe;
}

void DS18B20::scruter(void (*callback)(u8 num_rom))
{
	u8 cmd = 0x44;
	_ctrl->writeBroadcast(&cmd, 1);

	_ctrl->scruter(callback);
}

void DS18B20::setConfig(u8 num_rom, u8 precision, s8 temperatureBasse, s8 temperatureHaute)
{
	u8 cmd[4];
	cmd[0] = 0x4E;
	cmd[1] = temperatureHaute & 0x7F;
	cmd[2] = temperatureBasse & 0x7F;
	cmd[3] = ((precision&0X3) << 5) | 0x1F;
	_ctrl->write(num_rom, cmd, 4);
}

void DS18B20::sauvegarderConfig(u8 num_rom)
{
	u8 cmd = 0x48;
	_ctrl->write(num_rom, &cmd, 1);
}

void DS18B20::restaurerConfig(u8 num_rom)
{
	u8 cmd = 0xB8;
	_ctrl->write(num_rom, &cmd, 1);
}
