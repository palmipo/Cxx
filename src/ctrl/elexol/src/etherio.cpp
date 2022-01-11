#include "etherio.h"
#include <socketudp.h>
#include <iostream>
#include <iomanip>
#include <thread>

EtherIO::EtherIO(Socket::SocketUdp * sock)
: _socket(sock)
, _control_bit1(0xff)
, _control_bit2(0xff)
, _clb_get(0)
, _clb_direction(0)
, _clb_pullup(0)
, _clb_threshold(0)
, _clb_schmitt_trigger(0)
, _clb_echo(0)
, _clb_io24(0)
, _clb_host_data(0)
{}

EtherIO::~EtherIO()
{}

uint8_t EtherIO::getDirection(uint8_t port, void (*clb_direction)(uint8_t, uint8_t))
{
	_clb_direction = clb_direction;

	// direction
	uint8_t buffer[3];
	buffer[0] = 0x21;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);

	if (_clb_direction)
	{
		return 0;
	}
	else
	{
		// attendre 10ms
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		_socket->read(buffer, 3);
		return buffer[2];
	}
}

void EtherIO::setDirection(uint8_t port, uint8_t dir)
{
	uint8_t buffer[3];
	buffer[0] = 0x21;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = dir;
	_socket->write(buffer, 3);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 3);
}

uint8_t EtherIO::getPullup(uint8_t port, void (*clb_pullup)(uint8_t, uint8_t))
{
	_clb_pullup = clb_pullup;

	uint8_t buffer[3];
	buffer[0] = 0x40;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);

	if (_clb_pullup)
	{
		return 0;
	}
	else
	{
		// attendre 10ms
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		_socket->read(buffer, 3);
		return buffer[2];
	}
}

void EtherIO::setPullup(uint8_t port, uint8_t pullup)
{
	uint8_t buffer[3];
	buffer[0] = 0x40;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = pullup;
	_socket->write(buffer, 3);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 3);
}

uint8_t EtherIO::getThreshold(uint8_t port, void (*clb_threshold)(uint8_t, uint8_t))
{
	_clb_threshold = clb_threshold;

	uint8_t buffer[3];
	buffer[0] = 0x23;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);

	if (_clb_threshold)
	{
		return 0;
	}
	else
	{
		// attendre 10ms
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		_socket->read(buffer, 3);
		return buffer[2];
	}
}

void EtherIO::setThreshold(uint8_t port, uint8_t threshold)
{
	uint8_t buffer[3];
	buffer[0] = 0x23;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = threshold;
	_socket->write(buffer, 3);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 3);
}

uint8_t EtherIO::getSchmitt(uint8_t port, void (*clb_schmitt_trigger)(uint8_t, uint8_t))
{
	_clb_schmitt_trigger = clb_schmitt_trigger;

	uint8_t buffer[3];
	buffer[0] = 0x24;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);

	if (_clb_schmitt_trigger)
	{
		return 0;
	}
	else
	{
		// attendre 10ms
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		_socket->read(buffer, 3);
		return buffer[2];
	}
}

void EtherIO::setSchmitt(uint8_t port, uint8_t schmitt)
{
	uint8_t buffer[3];
	buffer[0] = 0x24;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = schmitt;
	_socket->write(buffer, 3);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 3);
}

uint8_t EtherIO::get(uint8_t port, void (*clb_get)(uint8_t, uint8_t))
{
	_clb_get = clb_get;

	//~ int32_t nBytes;
	uint8_t buffer[2];
	buffer[0] = 0x61 + (port & 0x03);
	_socket->write(buffer, 1);

	if (_clb_get)
	{
		return 0;
	}
	else
	{
		// attendre 10ms
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		_socket->read(buffer, 2);
		return buffer[1];
	}
}

void EtherIO::set(uint8_t port, uint8_t value)
{
	uint8_t buffer[2];
	buffer[0] = 0x41 + (port & 0x03);
	buffer[1] = value;
	_socket->write(buffer, 2);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 3);
}

void EtherIO::resetModule()
{
	writeEnableEEPROM();

	uint8_t buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x52;
	buffer[2] = 0x00;
	buffer[3] = 0xAA;
	buffer[4] = 0x55;
	_socket->write(buffer, 5);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 4);
}

void EtherIO::readEEPROM(uint8_t addr, uint8_t *lsb, uint8_t *msb)
{
	uint8_t buffer[5];
	buffer[0] = 0x27;
	buffer[1] = 0x52;
	buffer[2] = addr;
	buffer[3] = 0;
	buffer[4] = 0;
	_socket->write(buffer, 5);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 4);
	*msb = buffer[2];
	*lsb = buffer[3];
}

void EtherIO::writeEEPROM(uint8_t addr, uint8_t lsb, uint8_t msb)
{
	writeEnableEEPROM();

	uint8_t buffer[5];
	buffer[0] = 0x27;
	buffer[1] = 0x57;
	buffer[2] = addr;
	buffer[3] = msb;
	buffer[4] = lsb;
	_socket->write(buffer, 5);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 4);
}

void EtherIO::eraseEEPROM(uint8_t addr)
{
	writeEnableEEPROM();

	uint8_t buffer[5];
	buffer[0] = 0x27;
	buffer[1] = 0x45;
	buffer[2] = addr;
	buffer[3] = 0xAA;
	buffer[4] = 0x55;
	_socket->write(buffer, 5);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 4);
}

void EtherIO::writeEnableEEPROM()
{
	uint8_t buffer[5];
	buffer[0] = 0x27;
	buffer[1] = 0x31;
	buffer[2] = 0;
	buffer[3] = 0xAA;
	buffer[4] = 0x55;
	_socket->write(buffer, 5);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 4);
}

void EtherIO::writeDisableEEPROM()
{
	uint8_t buffer[5];
	buffer[0] = 0x27;
	buffer[1] = 0x30;
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	_socket->write(buffer, 5);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_socket->read(buffer, 4);
}

void EtherIO::identifyUnit(void (*clb_io24)(uint8_t*, uint8_t*))
{
	_clb_io24 = clb_io24;

	//~ int32_t nBytes;
	uint8_t buffer[1024];
	buffer[0] = 0x49;
	buffer[1] = 0x4F;
	buffer[2] = 0x32;
	buffer[3] = 0x34;
	_socket->write(buffer, 4);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	//~ 6 Byte MAC Address 
	//~ 2 Byte Firmware Version
	_socket->read(buffer, 12);

	if (_clb_io24)
	{
		clb_io24(buffer, buffer+6);
	}
}

void EtherIO::sendHostData(void (*clb_host_data)(uint32_t, uint8_t*, uint8_t*, uint16_t))
//~ void EtherIO::sendHostData()
{
	_clb_host_data = clb_host_data;

	int32_t nBytes;
	uint8_t buffer[1024];
	buffer[0] = 0x25;
	_socket->write(buffer, 1);

	// attendre 10ms
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	//~ 4 byte IO24 Serial 
	//~ 4 byte Sender IP 
	//~ 6 byte Sender MAC 
	//~ 2 Byte Sender Port 
	_socket->read(buffer, 16);

	if (_clb_host_data)
	{
		_clb_host_data((buffer[1] << 16) | (buffer[2] << 8) | buffer[3], buffer+4, buffer+8, (buffer[14] << 8) | buffer[15]);
	}
}

void EtherIO::setIpFixe(uint8_t * ip)
{	
	// 5 Control Bits 2 / Control Bits 1 
	// The currently used bits are :
	// bit 0, which is used to enable the Fixed IP address
	// Bit 1, which is used to enable the Preset Port function
	// Bit 2, which is used to enable the AutoScan function
	_control_bit1 &= ~(0x01);
	_control_bit2 = 0xff;
	writeEEPROM(5, _control_bit1, _control_bit2);

	// 6 13 Fixed IP Address Byte 2			12 Fixed IP Address Byte 1 
	writeEEPROM(6, ip[1], ip[2]);
	// 7 15 Fixed IP Address Byte 4			14 Fixed IP Address Byte 3 
	writeEEPROM(7, ip[3], ip[4]);
}
	
void EtherIO::setPresetPort(uint8_t * Preset, uint8_t * Direction, uint8_t * Pull_Up, uint8_t * Threshold, uint8_t * SchmittTrigger)
{
	_control_bit1 &= ~(0x02);
	_control_bit2 = 0xff;
	writeEEPROM(5, _control_bit1, _control_bit2);

	// 8 17 Preset Port A Direction			16 Preset Port A Value 
	writeEEPROM(8, Preset[0], Direction[0]);
	// 9 19 Preset Port A Threshold			18 Preset Port A Pull-Up 
	writeEEPROM(9, Pull_Up[0], Threshold[0]);
	// 10 21 Preset Port B Value			20 Preset Port A Schmitt Trigger 
	writeEEPROM(10, SchmittTrigger[0], Preset[1]);
	// 11 23 Preset Port B Pull-Up			22 Preset Port B Direction 
	writeEEPROM(11, Direction[1], Pull_Up[1]);
	// 12 25 Preset Port B Schmitt Trigger 	24 Preset Port B Threshold 
	writeEEPROM(12, Threshold[1], SchmittTrigger[1]);
	// 13 27 Preset Port C Direction		26 Preset Port C Value 
	writeEEPROM(13, Preset[2], Direction[2]);
	// 14 29 Preset Port C Threshold		28 Preset Port C Pull-Up 
	writeEEPROM(14, Pull_Up[2], Threshold[2]);
	// 15 31 Reserved for Future Use		30 Preset Port C Schmitt Trigger 
	writeEEPROM(15, SchmittTrigger[2], 0xFF);
}
	
void EtherIO::setAutoScan(uint8_t maskPortA, uint8_t maskPortB, uint8_t maskPortC, uint8_t filterCount, uint16_t autoScanRate, uint8_t * mac_addr, uint8_t * ip_addr, uint16_t port_addr)
{
	_control_bit1 &= ~(0x04);
	_control_bit2 = 0xff;
	writeEEPROM(5, _control_bit1, _control_bit2);

	// 16 33 AutoScan Port B Mask			32 AutoScan Port A Mask
	// 17 35 AutoScan Filter Count			34 AutoScan Port C Mask
	// 18 37 AutoScan Scan Rate MSB			36 AutoScan Scan Rate LSB
	writeEEPROM(16, maskPortA, maskPortB);
	writeEEPROM(17, maskPortC, filterCount);
	writeEEPROM(18, (autoScanRate & 0xFF), (autoScanRate & 0xFF00) >> 8);

	// 19 38 AutoScan Target MAC Address 1		39 AutoScan Target MAC Address 2
	// 20 40 AutoScan Target MAC Address 3		41 AutoScan Target MAC Address 4
	// 21 42 AutoScan Target MAC Address 5		43 AutoScan Target MAC Address 6
	writeEEPROM(19, mac_addr[1], mac_addr[0]);
	writeEEPROM(20, mac_addr[3], mac_addr[2]);
	writeEEPROM(21, mac_addr[5], mac_addr[4]);

	// 22 44 AutoScan Target IP Address 1		45 AutoScan Target IP Address 2
	// 23 46 AutoScan Target IP Address 3		47 AutoScan Target IP Address 4
	writeEEPROM(22, ip_addr[1], ip_addr[0]);
	writeEEPROM(23, ip_addr[3], ip_addr[2]);

	// 24 48 AutoScan Target Port LSB			49 AutoScan Target Port MSB
	writeEEPROM(24, (port_addr & 0xFF00) >> 8, (port_addr & 0x00FF));
}

void EtherIO::decode(uint8_t *data, int32_t length)
{
	switch (data[0])
	{
		// valeur
		case 0x61 :
		case 0x62 :
		case 0x63 :
			if (_clb_get)
			{
				_clb_get(data[0] - 0x61, data[1]);
			}
			break;
		
		// direction
		case 0x21 :
			if (_clb_direction)
			{
				_clb_direction(data[1] - 0x41, data[2]);
			}
			break;
		
		// pull-up
		case 0x40:
			if (_clb_pullup)
			{
				_clb_pullup(data[1] - 0x41, data[2]);
			}
			break;
		
		//threshold
		case 0x23:
			if (_clb_threshold)
			{
				_clb_threshold(data[1] - 0x41, data[2]);
			}
			break;
		
		// schmitt trigger
		case 0x24:
			if (_clb_schmitt_trigger)
			{
				_clb_schmitt_trigger(data[1] - 0x41, data[2]);
			}
			break;
		
		// read eeprom
		case 0x52:
			if (data[1] == 5)
			{
				_control_bit2 = data[2];
				_control_bit1 = data[3];
			}
			break;
		
		// echo
		case 0x60:
			if (_clb_echo)
			{
				_clb_echo(data[1]);
			}
			break;
		
		// io24
		case 0x49:
			if (_clb_io24)
			{
				_clb_io24(data+4, data+10);
			}
			break;
		
		// host data
		case 0x25:
			if (_clb_host_data)
			{
				_clb_host_data((data[1] << 16) | (data[2] << 8) | data[3], data+4, data+8, (data[14] << 8) | data[15]);
			}
			break;
			
		default:
			std::cerr << "reception message inconnu : 0x" << std::hex << (int)data[0] << std::dec << std::endl;
	}
}
