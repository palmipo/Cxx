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
, _buffer(0)
{
	_serial = add(device);
	_serial->setConfig(B115200, 8, 'N', 1, 0);
	// _serial->setInterCharacterTimer(0xFF);
	// _serial->setBlockingReadUntilCharacter(2);
}

SIM900::~SIM900()
{
	send_cmd("ATE1");

	delete _buffer;
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
		return 1;
	}

	Sim900Buffer * buffer = _fifo.front();
	_fifo.pop();

	int32_t len = 0;
	std::string recv(512, 0);
	len = buffer->read((uint8_t*)recv.data(), 512);
	delete buffer;
	
	if (recv.find("OK") == std::string::npos)
	{
		return 1;
	}
	
	return 0;
}

void SIM900::atz()
{
	try
	{
		send_cmd("ATZ");
	}
	catch(...)
	{}
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
	try
	{
		std::stringstream ss2;
		ss2 << (int8_t)13 << (int8_t)10 << "AT+CMGL=" << (int8_t)0x22 << "ALL" << (int8_t)0x22 << (int8_t)13 << (int8_t)10;
		std::string cmd = ss2.str();
		Log::getLogger()->debug(__FILE__, __LINE__, cmd);
		_serial->write((uint8_t *)cmd.c_str(), cmd.size());
	}
	catch(...)
	{}
}

void SIM900::write_sms(const std::string & num_tel, const std::string & texte)
{
	_texte_sms = texte;

	// envoi sms
	std::stringstream ss;
	ss << "AT+CMGS=" << (int8_t)0x22 << num_tel << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
}

void SIM900::read_sms(int32_t num)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CMGR=" << num << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	Log::getLogger()->debug(__FILE__, __LINE__, cmd);
	_serial->write((uint8_t *)cmd.c_str(), cmd.size());
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

		if (cpt > 1)
		{
			if ((data[cpt-2] == 0xd) && (data[cpt-1] == 0xa))
			{
				if (data[0] == '+' )
				{
					Log::getLogger()->info(__FILE__, __LINE__, (const char *)data);
					// if (cmd.find("+CMGR") != std::string::npos)
					{
						/*
						+CMGR: "REC READ","+33695245395","","19/10/03,07:42:21+08"
						Hello

						OK
						*/
					}
				}
				else
				{
					Sim900Buffer * buffer = new Sim900Buffer();
					buffer->write(data, cpt);
					_fifo.push(buffer);
				}
			}
			else if ((data[cpt-2] == '>') && (data[cpt-1] == 0x20))
			{
				device->write((uint8_t *)_texte_sms.c_str(), _texte_sms.length());
				uint8_t ctrl_z = 0x1A;
				device->write(&ctrl_z, 1);
			}
		}
	}
	while (nb && (retry < max_retry));
	

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
