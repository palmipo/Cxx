#include "etherio.h"
#include <socketudp.h>
#include <iostream>
#include <iomanip>
#include "poll.h"

EtherIO::EtherIO(Socket::SocketUdp * sock)
: PIA()
, _socket(sock)
{}

EtherIO::~EtherIO()
{}

u8 EtherIO::getDirection(u8 port)
{
	u8 buffer[3];

	// direction
	buffer[0] = 0x21;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);
	_socket->read(buffer, 3);

	return buffer[2];
}

u8 EtherIO::getPullup(u8 port)
{
	u8 buffer[3];

	// direction
	buffer[0] = 0x40;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);
	_socket->read(buffer, 3);

	return buffer[2];
}

u8 EtherIO::getThreshold(u8 port)
{
	u8 buffer[3];

	// direction
	buffer[0] = 0x23;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);
	_socket->read(buffer, 3);

	return buffer[2];
}

u8 EtherIO::getSchmitt(u8 port)
{
	u8 buffer[3];

	// direction
	buffer[0] = 0x24;
	buffer[1] = 0x61 + (port & 0x03);
	_socket->write(buffer, 3);
	_socket->read(buffer, 3);

	return buffer[2];
}

void EtherIO::setDirection(u8 port, u8 dir)
{
	u8 buffer[3];

	// direction
	buffer[0] = 0x21;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = dir;
	_socket->write(buffer, 3);
}

void EtherIO::setPullup(u8 port, u8 pullup)
{
	u8 buffer[3];

	buffer[0] = 0x40;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = pullup;
	_socket->write(buffer, 3);
}

void EtherIO::setThreshold(u8 port, u8 threshold)
{
	u8 buffer[3];

	buffer[0] = 0x23;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = threshold;
	_socket->write(buffer, 3);
}

void EtherIO::setSchmitt(u8 port, u8 schmitt)
{
	u8 buffer[3];

	buffer[0] = 0x24;
	buffer[1] = 0x41 + (port & 0x03);
	buffer[2] = schmitt;
	_socket->write(buffer, 3);
}

void EtherIO::set(u8 port, u8 value)
{
	u8 buffer[2];

	buffer[0] = 0x41 + (port & 0x03);
	buffer[1] = value;
	_socket->write(buffer, 2);
}

u8 EtherIO::get(u8 port)
{
	s32 nBytes;
	u8 buffer[2];
	buffer[0] = 0x61 + (port & 0x03);
	_socket->write(buffer, 1);
	_socket->read(buffer, 2);
	
	return buffer[1];
}

void EtherIO::resetModule()
{
	u8 buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x52;
	buffer[2] = 0x00;
	buffer[3] = 0xAA;
	buffer[4] = 0x55;
	_socket->write(buffer, 5);
}

void EtherIO::setAutoScan(u8 port, u8 filterCount, u16 autoScanRate/*, u8 * mac_addr, u8 * ip_addr, u16 port_addr*/)
{
	u8 buffer[16];
	buffer[0] = 0x25;
	_socket->write(buffer, 1);
	_socket->read(buffer, 16);

	std::cout << "send host data : " << std::hex;
	for (u8 i=0; i<16; i+=1)
		std::cout << (int)buffer[i] << " ";
	std::cout << std::dec << std::endl;
	
	enableEEPROM();

	// 5 11 Control Bits 2						10 Control Bits 1 
	// The currently used bits are :
	// bit 0, which is used to enable the Fixed IP address
	// Bit 1, which is used to enable the Preset Port function
	// Bit 2, which is used to enable the AutoScan function
	uint8_t ctrl = ~(ip_fixe | (preset_port << 1) | (autoscan << 2));
	writeEEPROM(5, ctrl, ctrl);

	// 6 13 Fixed IP Address Byte 2			12 Fixed IP Address Byte 1 
	writeEEPROM(6, 168, 192);
	// 7 15 Fixed IP Address Byte 4			14 Fixed IP Address Byte 3 
	writeEEPROM(7, 2, 10);

	// 8 17 Preset Port A Direction			16 Preset Port A Value 
	writeEEPROM(8, 0, 0);
	// 9 19 Preset Port A Threshold			18 Preset Port A Pull-Up 
	writeEEPROM(9, 0, 0);
	// 10 21 Preset Port B Value			20 Preset Port A Schmitt Trigger 
	writeEEPROM(10, 0, 0);
	// 11 23 Preset Port B Pull-Up			22 Preset Port B Direction 
	writeEEPROM(11, 0, 0);
	// 12 25 Preset Port B Schmitt Trigger 	24 Preset Port B Threshold 
	writeEEPROM(12, 0, 0);
	// 13 27 Preset Port C Direction		26 Preset Port C Value 
	writeEEPROM(13, 0xFF, 0);
	// 14 29 Preset Port C Threshold		28 Preset Port C Pull-Up 
	writeEEPROM(14, 0, 0);
	// 15 31 Reserved for Future Use		30 Preset Port C Schmitt Trigger 
	writeEEPROM(15, 0xFF, 0xFF);

	// 16 33 AutoScan Port B Mask			32 AutoScan Port A Mask
	// 17 35 AutoScan Filter Count			34 AutoScan Port C Mask
	// 18 37 AutoScan Scan Rate MSB			36 AutoScan Scan Rate LSB
	writeEEPROM(16, 0xFF, 0xFF);
	writeEEPROM(17, filterCount, 0);
	writeEEPROM(18, autoScanRate>>8, autoScanRate&0xFF);

	// 19 38 AutoScan Target MAC Address 1		39 AutoScan Target MAC Address 2
	// 20 40 AutoScan Target MAC Address 3		41 AutoScan Target MAC Address 4
	// 21 42 AutoScan Target MAC Address 5		43 AutoScan Target MAC Address 6
	writeEEPROM(19, buffer[9], buffer[8]);
	writeEEPROM(20, buffer[11], buffer[10]);
	writeEEPROM(21, buffer[13], buffer[12]);

	// 22 44 AutoScan Target IP Address 1		45 AutoScan Target IP Address 2
	// 23 46 AutoScan Target IP Address 3		47 AutoScan Target IP Address 4
	writeEEPROM(22, buffer[5], buffer[4]);
	writeEEPROM(23, buffer[7], buffer[6]);

	// 24 48 AutoScan Target Port LSB			49 AutoScan Target Port MSB
	writeEEPROM(24, 24, 24);

	disableEEPROM();
}

u16 EtherIO::readEEPROM(u8 addr)
{
	u8 buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x52;
	buffer[2] = addr;
	buffer[3] = 0;
	buffer[4] = 0;
	_socket->write(buffer, 5);
	_socket->read(buffer, 4);
	
	u16 res = buffer[2]<<8;
	res |= buffer[3];
	return res;
}

void EtherIO::writeEEPROM(u8 addr, u8 msb, u8 lsb)
{
	u8 buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x57;
	buffer[2] = addr;
	buffer[3] = msb;
	buffer[4] = lsb;
	_socket->write(buffer, 5);
	poll(0, 0, 100);
}

void EtherIO::eraseEEPROM(u8 addr)
{
	u8 buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x45;
	buffer[2] = addr;
	buffer[3] = 0xAA;
	buffer[4] = 0x55;
	_socket->write(buffer, 5);
}

void EtherIO::enableEEPROM()
{
	u8 buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x31;
	buffer[2] = 0;
	buffer[3] = 0xAA;
	buffer[4] = 0x55;
	_socket->write(buffer, 5);
}

void EtherIO::disableEEPROM()
{
	u8 buffer[5];

	buffer[0] = 0x27;
	buffer[1] = 0x30;
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	_socket->write(buffer, 5);
}

void EtherIO::identifyUnit()
{
	s32 nBytes;
	u8 buffer[1024];
	buffer[0] = 0x49;
	buffer[1] = 0x4F;
	buffer[2] = 0x32;
	buffer[3] = 0x34;
	_socket->write(buffer, 4);
	nBytes = _socket->read(buffer, 12);
	std::cout << "reception " << nBytes << " bytes" << std::hex << std::endl;
	for (s32 i=0; i<nBytes; ++i)
	{
		std::cout << " 0x" << (s32)buffer[i];
	}
	std::cout << std::dec << std::endl;
}
