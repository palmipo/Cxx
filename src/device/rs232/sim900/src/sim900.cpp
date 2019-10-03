#include "sim900.h"
#include "rs232.h"
#include "log.h"
#include <string>
#include <thread>
#include <cstring>
#include <sstream>
#include <iostream>

// 115200 8N1
SIM900::SIM900(const std::string & device)
: RS232Factory()
{
	_serial = add(device);
	_serial->setConfig(B9600, 8, 'N', 1, 1);
	// _serial->setInterCharacterTimer(0xFF);
	// _serial->setBlockingReadUntilCharacter(2);

	{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));

	{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "ATE0" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

SIM900::~SIM900()
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "ATE1" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
}

void SIM900::atz()
{
	int32_t cpt = 0;
	int32_t length = 0;
	int8_t buffer[256];

	// reinitialisation de la config
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "ATZ" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::init_sms()
{
	// sms en mode texte
	std::stringstream ss2;
	ss2 << (int8_t)0x0D << (int8_t)0x0A << "AT+CMGF=1" << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd = ss2.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::get_clock()
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CCLK?" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::send_call(const std::string & num_tel)
{
	std::stringstream ss2;
	ss2 << (int8_t)13 << (int8_t)10 << "ATDT " << num_tel << ";" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss2.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::list_sms()
{
	std::stringstream ss2;
	ss2 << (int8_t)13 << (int8_t)10 << "AT+CMGL=\"ALL\"" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss2.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::send_sms(const std::string & num_tel, const std::string & texte)
{
	// envoi sms
	std::stringstream ss;
	ss << "AT+CMGS=" << (int8_t)0x22 << num_tel << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	
	_texte_sms = texte;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::recv_sms(int32_t num)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CMGR=" << num << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));

/*	int32_t cpt = 0;
	int32_t length = 0;
	int8_t buffer[256];
	length = read_uart(buffer, 256);

	while ((cpt < 10) && (length <100) && (buffer[length-2] != 13) && (buffer[length-1] != 10))
	{
		// if (_serial->scrute(TEMPO) > 0)
		{
			length += _serial->read(buffer+length, 1);
		}
		// else
		{
			cpt += 1;
		}
	}
*/
}

void SIM900::delete_sms(int32_t num)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CMGD=" << num << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}


int32_t SIM900::actionIn(PollDevice * device)
{
	device->actionIn();

	uint8_t data[512];
	int32_t retry = 0, nb, cpt = 0;
	do
	{
		nb = device->read(data+cpt, 512-cpt);
		cpt += nb;
		retry += 1;
	}
	while (nb && (retry < 5));
	
	std::string cmd((const char *)data);
	{
		std::stringstream ss;
		ss << "=> " << cmd << " <=";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	

	if (cmd.find("+CMGR") != std::string::npos)
	{
		/*
		+CMGR: "REC READ","+33695245395","","19/10/03,07:42:21+08"
		Hello

		OK
		*/
	}
	// attendre >_
	if (cmd.find(">") != std::string::npos)
	{
		_serial->write((uint8_t *)_texte_sms.c_str(), _texte_sms.size());
		int8_t ctrl_z = 0x1A;
		_serial->write((uint8_t *)&ctrl_z, 1);
	}

	return cpt;
}

int32_t SIM900::actionOut(PollDevice * device)
{
	int32_t len = device->actionOut();
	return len;
}

int32_t SIM900::actionError(PollDevice * device)
{
	int32_t len = device->actionError();
	return len;
}
