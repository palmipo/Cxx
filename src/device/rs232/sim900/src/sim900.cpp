#include "sim900.h"
#include "sim900exception.h"
#include "rs232.h"
#include "log.h"
#include <string>
#include <thread>
#include <cstring>
#include <sstream>
#include <iostream>

// 115200 8N1
SIM900::SIM900(RS232 * device)
: _serial(device)
{
	_serial->setConfig(B115200, 8, 'N', 1, 0);
	// _serial->setInterCharacterTimer(0xFF);
	// _serial->setBlockingReadUntilCharacter(2);
}

SIM900::~SIM900()
{
	send_cmd("ATE1");
}

int32_t SIM900::send_cmd(const std::string & cmd)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << cmd << (int8_t)13 << (int8_t)10;
	std::string snd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, snd);
	_serial->write((uint8_t *)snd.c_str(), snd.size());

	uint8_t data[512];
	int32_t len = _serial->read(data, 512);

	if (std::string((char *)data) == "OK")
	{
		return 1;
	}

	return 0;
}

void SIM900::atz()
{
	send_cmd("ATZ");
}

void SIM900::init_sms()
{
	send_cmd("AT");
	send_cmd("ATE0");
	send_cmd("AT+CMGF=1");
}

void SIM900::get_clock()
{
	send_cmd("AT+CCLK?");
}

void SIM900::send_call(const std::string & num_tel)
{
	std::stringstream ss2;
	ss2 << "ATDT " << num_tel << ";";

	send_cmd(ss2.str());
}

void SIM900::list_sms()
{
	std::stringstream ss2;
	ss2 << (int8_t)13 << (int8_t)10 << "AT+CMGL=" << (int8_t)0x22 << "ALL" << (int8_t)0x22 << (int8_t)13 << (int8_t)10;
	std::string cmd = ss2.str();

	send_cmd(cmd);
}

void SIM900::write_sms(const std::string & num_tel, const std::string & texte)
{
	// envoi sms
	std::stringstream ss;
	ss << "AT+CMGS=" << (int8_t)0x22 << num_tel << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd = ss.str();

	send_cmd(cmd);
}

void SIM900::read_sms(int32_t num)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CMGR=" << num << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();

	send_cmd(cmd);
}

void SIM900::delete_sms(int32_t num)
{
	std::stringstream ss;
	ss << "AT+CMGD=" << num;
	std::string cmd = ss.str();

	send_cmd(cmd);
}
