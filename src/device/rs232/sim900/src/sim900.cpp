#include "sim900.h"
#include "rs232.h"
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

// 115200 8N1
SIM900::SIM900(const std::string & device)
: RS232Factory()
{
	_serial = add(device);
	_serial->setConfig(B9600, 8, 'N', 1, 0);
	_serial->setInterCharacterTimer(0xFF);
	// _serial->setBlockingReadUntilCharacter(2);

	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "ATE0" << (int8_t)13 << (int8_t)10;
	std::string cmd1 = ss.str();
	_serial->write((int8_t*)cmd1.c_str(), cmd1.size());
}

SIM900::~SIM900()
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "ATE1" << (int8_t)13 << (int8_t)10;
	std::string cmd1 = ss.str();
	_serial->write((int8_t*)cmd1.c_str(), cmd1.size());
}

void SIM900::atz()
{
	int32_t cpt = 0;
	int32_t length = 0;
	int8_t buffer[256];

	// reinitialisation de la config
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "ATZ" << (int8_t)13 << (int8_t)10;
	std::string cmd1 = ss.str();
	_serial->write((int8_t*)cmd1.c_str(), cmd1.size());
}

void SIM900::init_sms()
{
	// sms en mode texte
	std::stringstream ss2;
	ss2 << (int8_t)0x0D << (int8_t)0x0A << "AT+CMGF=1" << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd2 = ss2.str();
	_serial->write((int8_t*)cmd2.c_str(), cmd2.size());
}

void SIM900::get_clock()
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CCLK?" << (int8_t)13 << (int8_t)10;
	std::string cmd = ss.str();
	_serial->write((int8_t*)cmd.c_str(), cmd.size());
}

void SIM900::send_call(const std::string & num_tel)
{
	std::stringstream ss2;
	ss2 << (int8_t)13 << (int8_t)10 << "ATDT " << num_tel << ";" << (int8_t)13 << (int8_t)10;
	std::string cmd2 = ss2.str();
	_serial->write((int8_t*)cmd2.c_str(), cmd2.size());
}

void SIM900::list_sms()
{
	std::stringstream ss2;
	ss2 << (int8_t)13 << (int8_t)10 << "AT+CMGL=\"ALL\"" << (int8_t)13 << (int8_t)10;
	std::string cmd2 = ss2.str();
	_serial->write((int8_t*)cmd2.c_str(), cmd2.size());
}

void SIM900::send_sms(const std::string & num_tel, const std::string & texte)
{
	// envoi sms
	std::stringstream ss;
	ss << (int8_t)0x0D << (int8_t)0x0A << "AT+CMGS=" << (int8_t)0x22 << num_tel << (int8_t)0x22 << (int8_t)0x0D << (int8_t)0x0A;
	std::string cmd = ss.str();
	_serial->write((int8_t*)cmd.c_str(), cmd.size());

/*
	// attendre >_
	int8_t reponse[256];
	int32_t cpt = _serial->get(reponse, 255);
	//~ int32_t cpt = read_uart(reponse, 255);

	if ((cpt == 2) && (reponse[0] = '>') && (reponse[1] == 0x20))
	{
		_serial->write((int8_t*)texte.c_str(), texte.size());
		int8_t ctrl_z = 0x1A;
		_serial->write((int8_t*)&ctrl_z, 1);
		//~ if (_serial->scrute(1000) > 0)
		{
			int8_t reponse[256];
			_serial->get(reponse, 255);
			//~ read_uart(reponse, 255);
		}
	}

	// attendre +CMGS:
	//~ _serial->get(reponse, 255);
	//~ read_uart(reponse, 255);
*/
}

void SIM900::recv_sms(int32_t num)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CMGR=" << num << (int8_t)13 << (int8_t)10;
	std::string cmd2 = ss.str();
	_serial->write((int8_t*)cmd2.c_str(), cmd2.size());

	int32_t cpt = 0;
	int32_t length = 0;
	int8_t buffer[256];
	length = read_uart(buffer, 256);

	while ((cpt < 10) && (length <100) && (buffer[length-2] != 13) && (buffer[length-1] != 10))
	{
		// if (_serial->scrute(TEMPO) > 0)
		{
			length += _serial->get(buffer+length, 1);
		}
		// else
		{
			cpt += 1;
		}
	}
}

void SIM900::delete_sms(int32_t num)
{
	std::stringstream ss;
	ss << (int8_t)13 << (int8_t)10 << "AT+CMGD=" << num << (int8_t)13 << (int8_t)10;
	std::string cmd2 = ss.str();
	_serial->write((int8_t*)cmd2.c_str(), cmd2.size());
}

void SIM900::reception_message(void * data)
{
	std::cout << "reception_message" << std::endl;

	SIM900 * uart = (SIM900 *)data;

	int32_t len = 0;
	int32_t cpt = 0;
	int32_t length = 0;
	int8_t buffer[100], buf[200];
	// if (uart->_serial->scrute(TEMPO) > 0)
	{
		len = uart->_serial->get(buffer, 100);
		while (len > 0)
		{
			for (int i=0; i<len; i+=1)
			{
				buf[length] = buffer[i];
				length += 1;
		
				if ((length > 2) && (buf[length - 2] == 13) && (buf[length - 1] == 10))
				{
					uart->analyse_message(buf, length-2);
					::memset(buf, 0, 100);
					length = 0;
				}
			}
			len = uart->_serial->get(buffer, 100);
		}
	}
}


int32_t SIM900::analyse_message(int8_t * buffer, int32_t length)
{
	std::cout << "analyse_message : " << std::endl;
	
	//+CCLK: "04/01/01,00:07:49+00"

	return 0;
}

int32_t SIM900::read_uart(int8_t * buffer, int32_t buffer_length)
{
	::memset(buffer, 0, buffer_length);

	int32_t len = 0;
	int32_t cpt = 0;
	do
	{
		len = _serial->get(buffer+cpt, buffer_length-cpt);
		cpt += len;
	}
	while ((len != 0) && (cpt < buffer_length));
	
	if (cpt > 0)
		std::cout << buffer << std::endl;

	return cpt;
}

int32_t SIM900::actionIn(PollDevice * device)
{
	int32_t len = device->actionIn();
	return len;
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
