#include "ixxatcanatnet.h"

#include "sockettcp.h"

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

/* constructeur socket client */
Ixxat::CanAtNet::CanAtNet(Socket::SocketTcp * socket)
: PollDevice(socket->handler())
, _socket(socket)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "CanAtNet !");

	int32_t baud_rate = 1000;

	std::stringstream ss;
	ss << "init " << baud_rate;
	writeCommand(ss.str());
}


Ixxat::CanAtNet::~CanAtNet()
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "~CanAtNet !");

	writeCommand("stop");
	
	delete _socket; _socket = 0;
}

int32_t Ixxat::CanAtNet::writeCommand(const std::string & cmd)
{
	std::stringstream ss1;
	ss1 << "c " << cmd << "\r\n";
	std::string msg1 = ss1.str();
	return _socket->write((u8 *)msg1.c_str(), msg1.length());
}
//  4d 20 53 44 38 20 30 36 30 35 20 34 30 20 31 38 20 31 30 20 30 33 20 30 30 20 30 30 20 30 30 20 30 30 20 0d 0a
int32_t Ixxat::CanAtNet::writeData(uint16_t node_id, uint8_t * data, int32_t data_length)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "writeData !");

	std::stringstream ss1;
	ss1 << "M SD" << data_length << ' ' << std::to_string((int)node_id) << ' ';
	for (int32_t i=0; i<data_length; ++i)
	{
		ss1 << std::to_string((int)data[i]) << ' ';
	}
	ss1 << "\r\n";

	std::string msg = ss1.str();
	return _socket->write((u8 *)msg.c_str(), msg.length());
}

int32_t Ixxat::CanAtNet::readData(uint16_t * node_id, uint8_t * data, int32_t data_length)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "readData !");

	int32_t len = 0;
	if (!_fifo.empty())
	{
		CanBuffer buffer = _fifo.front();
		_fifo.pop();
		
		*node_id = buffer.node_id;
		len = buffer.data.size();
		for (int32_t i=0; i<len; ++i)
		{
			data[i] = buffer.data[i];
		}
	}

	return len;
}

void Ixxat::CanAtNet::close()
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "close !");

	_socket->close();
}

int32_t Ixxat::CanAtNet::actionError()
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "actionError !");

	return _socket->actionError();
}

int32_t Ixxat::CanAtNet::actionIn()
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "actionIn !");

	int8_t msg[512];
	int32_t msg_length = _socket->read((u8 *)msg, 512);
	if (msg_length > 0)
	{
		std::stringstream ss(std::string((const char *)msg));
		std::string sousChaine;
		while(getline(ss, sousChaine, '\n'))
		{
			std::vector<std::string> elements;
			std::stringstream sss(sousChaine);
			std::string sousSousChaine;
			while (getline(sss, sousSousChaine, ' '))
			{
				elements.push_back(sousSousChaine);
			}
			LOG4CXX_DEBUG(logger, "msg " << sousChaine);

			if (elements.size() > 1)
			{
				LOG4CXX_DEBUG(logger, "commande " << elements[0]);
				if (elements[0] == "M")
				{
					const char * instruction = elements[1].c_str();
					CanBuffer buffer;
					buffer.node_id = std::strtoul(elements[2].c_str(), 0, 16);
					int32_t cpt = 0;
					buffer.data.resize(std::strtoul(instruction+2, 0, 10));
					LOG4CXX_DEBUG(logger, "instruction " << buffer.data.size());
					for (int32_t i=3; i<buffer.data.size(); ++i)
					{
						buffer.data[cpt] = std::strtoul(elements[i].c_str(), 0, 16);
						cpt += 1;
					}
					_fifo.push(buffer);
					LOG4CXX_DEBUG(logger, "buffer.data.size() " << buffer.data.size());
					LOG4CXX_DEBUG(logger, "_fifo.size() " << _fifo.size());
				}
				else if (elements[0] == "I")
				{
					if (elements[1] == "OK")
					{
						if ((elements[2] == "(CAN") && (elements[3] == "controller") && (elements[4] == "is") && (elements[5] == "initialized"))
						{
							writeCommand("start");
						}
					}
				}
				else if (elements[0] == "E")
				{
				}
			}
		}
	}
}

int32_t Ixxat::CanAtNet::actionOut()
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Ixxat::CanAtNet"));
	LOG4CXX_DEBUG(logger, "actionOut !");

	return _socket->actionOut();
}

