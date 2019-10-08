#include "sim900.h"
#include "sim900buffer.h"
#include "sim900exception.h"
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
	_serial->setConfig(B9600, 8, 'N', 1, 0);
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

	int32_t max_retry = 10;
	int32_t timeout = 1000;
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo.empty())
	{
		throw Sim900Exception(__FILE__, __LINE__, "fifo vide !");
	}

	Sim900Buffer * buffer = _fifo.front();
	_fifo.pop();

	int32_t len = 0;
	std::string recv(512, 0);
	len = buffer->read((uint8_t*)recv.data(), 512);
	delete buffer;
	
	if (recv.find("OK") != std::string::npos)
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
	ss2 << (int8_t)13 << (int8_t)10 << "AT+CMGL=\"ALL\"" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss2.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SIM900::write_sms(const std::string & num_tel, const std::string & texte)
{
	// envoi sms
	std::stringstream ss;
	ss << "AT+CMGS=" << (int8_t)0x22 << num_tel << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	
	int32_t max_retry = 10;
	int32_t timeout = 1000;
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo.empty())
	{
		throw Sim900Exception(__FILE__, __LINE__, "fifo vide !");
	}

	Sim900Buffer * buffer = _fifo.front();
	_fifo.pop();

	int32_t len = 0;
	std::string recv(512, 0);
	len = buffer->read((uint8_t *)recv.data(), 512);
	delete buffer;

	// attendre >_
	if (recv.find(">") != std::string::npos)
	{
		_serial->write((uint8_t *)_texte_sms.c_str(), _texte_sms.size());
		int8_t ctrl_z = 0x1A;
		_serial->write((uint8_t *)&ctrl_z, 1);
	}

	
	max_retry = 10;
	timeout = 1000;
	retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo.empty())
	{
		throw Sim900Exception(__FILE__, __LINE__, "fifo vide !");
	}

	buffer = _fifo.front();
	_fifo.pop();

	len = 0;
	len = buffer->read((uint8_t *)recv.data(), 512);
	delete buffer;
}

void SIM900::read_sms(int32_t num)
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
	ss << "AT+CMGD=" << num;
	send_cmd(ss.str());
}


int32_t SIM900::actionIn(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	/* util dans le cas d'un FIFO */
	device->actionIn();

	uint8_t data[512];
	int32_t max_retry = 5, retry = 0, nb, cpt = 0;
	do
	{
		nb = device->read(data+cpt, 512-cpt);
		cpt += nb;
		retry += 1;
	}
	while (nb && (retry < max_retry) && (data[cpt-2] != 0xd) && (data[cpt-1] != 0xa));
	
	std::string cmd((const char *)data);
	{
		std::stringstream ss;
		ss << "=> " << cmd << " <=";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	

	if (cmd.find("+") != 0)
	{
		Sim900Buffer * buffer = new Sim900Buffer();
		buffer->write(data, cpt);
		_fifo.push(buffer);
	}
	else
	{
		if (cmd.find("+CMGR") != std::string::npos)
		{
			/*
			+CMGR: "REC READ","+33695245395","","19/10/03,07:42:21+08"
			Hello

			OK
			*/
		}
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
