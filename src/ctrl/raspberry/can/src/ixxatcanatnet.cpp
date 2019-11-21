#include "ixxatcanatnet.h"
#include "canexception.h"
#include "sockettcp.h"
#include <sstream>
#include <thread>
#include <iomanip>

/* constructeur socket client */
Ixxat::CanAtNet::CanAtNet(uint16_t cob_id, PollDevice * device)
: CAN::Bus(cob_id, device)
{}

Ixxat::CanAtNet::~CanAtNet()
{
	writeCommand("stop");
}

void Ixxat::CanAtNet::init(int32_t baud_rate)
{
	std::stringstream ss;
	ss << "init " << baud_rate;
	if (!writeCommand(ss.str()))
	{
		throw CAN::Exception(__FILE__, __LINE__, "erreur initialisation IXXAT::Can@Net.");
	}

	if (!writeCommand("start"))
	{
		throw CAN::Exception(__FILE__, __LINE__, "erreur start IXXAT::Can@Net.");
	}

	// attendre la fin de la sequence d'initialisation
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

int32_t Ixxat::CanAtNet::writeCommand(const std::string & cmd, int32_t max_retry, int32_t timeout)
{
	std::stringstream ss1;
	ss1 << "c " << cmd << "\r\n";
	std::string msg1 = ss1.str();
	int32_t len = _device->write((uint8_t *)msg1.c_str(), msg1.length());

	int32_t retry = 0;
	while (_cmd_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_cmd_fifo.empty())
	{
		throw CAN::Exception(__FILE__, __LINE__, "fifo vide");
	}

	std::vector < std::string > buffer = _cmd_fifo.front();
	_cmd_fifo.pop();

	return (buffer[1] == "OK");
}

int32_t Ixxat::CanAtNet::writeData(uint16_t node_id, uint8_t * data, int32_t data_length)
{
	std::stringstream ss1;
	ss1 << "M SD" << data_length << ' ';
	ss1 << std::setfill('0') << std::setw(4) << std::hex << (int)node_id << ' ';
	for (int32_t i=0; i<data_length; ++i)
	{
		ss1 << std::setfill('0') << std::setw(2) << std::hex << (int)data[i];
		ss1 << ' ';
	}
	ss1 << "\r\n";

	{
		std::stringstream ss_log;
		ss_log << "writeData => msg : " << ss1.str();
		Log::getLogger()->debug(__FILE__, __LINE__, ss_log.str());
	}

	std::string msg = ss1.str();
	return _device->write((uint8_t *)msg.c_str(), msg.length());
}

int32_t Ixxat::CanAtNet::readData(uint16_t * node_id, uint8_t * data, int32_t data_length, int32_t max_retry, int32_t timeout)
{
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo.empty())
	{
		throw CAN::Exception(__FILE__, __LINE__, "fifo vide");
	}

	CAN::CANBuffer * buffer = _fifo.front();
	_fifo.pop();
	
	*node_id = buffer->cob_id;
	int32_t len = buffer->read(data, data_length);
	delete buffer;

	return len;
}

int32_t Ixxat::CanAtNet::actionIn(uint8_t * msg, int32_t msg_length)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	int32_t return_length = 0;
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
			{
				std::stringstream ss_log;
				ss_log << "actionIn => msg : " << sousChaine;
				Log::getLogger()->debug(__FILE__, __LINE__, ss_log.str());
			}
			if (elements.size() > 1)
			{
				if (elements[0] == "M")
				{
					uint16_t cob_id = std::strtoul(elements[2].c_str(), 0, 16);
					// if (cob_
					{
						const char * instruction = elements[1].c_str();
						int32_t len = std::strtol(instruction+2, 0, 0);
						CAN::CANBuffer * buffer = new CAN::CANBuffer();
						buffer->cob_id = cob_id;
						
						int32_t cpt = 0;
						std::vector < uint8_t > data(len);
						for (int32_t i=0; i<data.size(); ++i)
						{
							data[cpt] = std::strtoul(elements[3+i].c_str(), 0, 16);
							cpt += 1;
						}
						return_length += buffer->write(data.data(), cpt);
						_fifo.push(buffer);
					}
					// {
						// std::stringstream ss_log;
						// ss_log << "taille du buffer : " << _fifo.size() << " buffer length : " << return_length;
						// Log::getLogger()->debug(__FILE__, __LINE__, ss_log.str());
					// }
				}
				else if (elements[0] == "I")
				{
					{
						std::stringstream ss_log;
						ss_log << "information message : " << sousChaine;
						Log::getLogger()->error(__FILE__, __LINE__, ss_log.str());
					}
					_cmd_fifo.push(elements);
				}
				else if (elements[0] == "E")
				{
					{
						std::stringstream ss_log;
						ss_log << "error message : " << sousChaine;
						Log::getLogger()->error(__FILE__, __LINE__, ss_log.str());
					}
				}
			}
		}
	}
	
	return return_length;
}

int32_t Ixxat::CanAtNet::actionOut(uint8_t *, int32_t)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	return 0;
}

int32_t Ixxat::CanAtNet::actionError(uint8_t *, int32_t)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionError");

	return 0;
}

