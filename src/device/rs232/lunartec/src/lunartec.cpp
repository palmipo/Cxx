#include "lunartec.h"
#include "ctrluart.h"
#include "rs232exception.h"
#include <sstream>
#include <iomanip>
#include <time.h>

Lunartec::Lunartec(int32_t id, CtrlUART * serial)
: _id(id), _usart(serial)
{
	/* _usart->setConfig(B9600, 8, 'N', 1, 1); */

	std::stringstream cmd;
	cmd << std::string("<ID><");
	cmd << std::setw(2) << std::setfill('0') << std::setbase(10) << (_id & 0xFF);
	cmd << std::string("><E>");
	_usart->write((uint8_t *)cmd.str().c_str(), cmd.str().length());
}

Lunartec::~Lunartec()
{}

void Lunartec::set_time ()
{
	time_t tt = time(0);
	struct tm * t = localtime(&tt);

	std::stringstream data;
	data << std::string("<SC>");
	data << std::setw(2) << std::setfill('0') << t->tm_year-100;
	data << std::setw(2) << std::setfill('0') << t->tm_wday;
	data << std::setw(2) << std::setfill('0') << t->tm_mon+1;
	data << std::setw(2) << std::setfill('0') << t->tm_mday;
	data << std::setw(2) << std::setfill('0') << t->tm_hour;
	data << std::setw(2) << std::setfill('0') << t->tm_min;
	data << std::setw(2) << std::setfill('0') << t->tm_sec;

	write(data.str());
}

void Lunartec::send (const std::string & text, int8_t page, int8_t speed)
{
	std::stringstream data;
	data << std::string("<L1><P");
	data << page;
	data << std::string("><FA><M");
	data << speed;
	data << std::string("><WA><FA>");

	if (page == 'A')
	{
		data << text.substr(0, 80);
	}
	else if (page == 'B')
	{
		data << text.substr(0, 420);
	}
	else
	{
		throw RS232Exception(__FILE__, __LINE__, "Lunartec::send()");
	}

	write(data.str());
}

void Lunartec::write(const std::string & data)
{
	std::stringstream cmd;
	cmd << std::string("<ID");
	cmd << std::setw(2) << std::setfill('0') << std::setbase(10) << _id;
	cmd << std::string(">");
	cmd << data;
	cmd << std::setw(2) << std::setfill('0') << std::setbase(16) << (int)check_sum(data);
	cmd << std::string("<E>");
	_usart->write((uint8_t *)cmd.str().c_str(), cmd.str().length());
}

uint8_t Lunartec::check_sum(const std::string & text)
{
	uint8_t cs = 0;

	for (uint32_t i=0; i<text.length(); i++)
	{
		cs ^= text[i];
	}

	return cs;
}

