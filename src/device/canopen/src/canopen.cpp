#include "canopen.h"

#include "canbus.h"
#include "canexception.h"

#include "canopenpdo.h"
#include "canopensdo.h"
#include "canopennmt.h"
#include "canopenemcy.h"
#include "canopenguard.h"
#include "canopensync.h"
#include "canopenbuffer.h"
#include "canopenexception.h"
#include "canopenfifo.h"

#include "log.h"

#include <sstream>
#include <iomanip>

CAN::CANOpen::CANOpen(uint16_t node_id, CAN::Bus * interface_can, PollDevice * device)
: TowerDevice(device)
, _bus_can(interface_can)
, _node_id(node_id)
, _map_nmt(0)
, _map_emergency(0)
, _map_sdo(0)
, _map_sync(0)
{}

CAN::CANOpen::~CANOpen()
{
	delete _map_sync;
	delete _map_nmt;
	delete _map_emergency;
	delete _map_sdo;
	{
		std::map < uint8_t, CANOpenPDO * >::iterator it = _map_pdo.begin();
		while (it != _map_pdo.end())
		{
			delete it->second; it->second = 0;
			it++;
		}
	}
	{
		std::map < uint8_t, CANOpenFifo * >::iterator it = _map_fifo.begin();
		while (it != _map_fifo.end())
		{
			delete it->second; it->second = 0;
			it++;
		}
	}
}

PollDevice * CAN::CANOpen::get(uint8_t pdo_id)
{
	//~ uint8_t fct = pdo_id;
	switch (pdo_id)
	{
		case MNT_ID:
			return (PollDevice *)nmt();
			break;

		case EMGY_ID:
			return (PollDevice *)emergency();
			break;

		case PDO1_ID_RX:
		case PDO1_ID_TX:
		case PDO2_ID_RX:
		case PDO2_ID_TX:
		case PDO3_ID_RX:
		case PDO3_ID_TX:
		case PDO4_ID_RX:
		case PDO4_ID_TX:
			return (PollDevice *)pdo(pdo_id);
			break;

		case SDO_ID_RX:
		case SDO_ID_TX:
			return (PollDevice *)sdo();
			break;

		case GUARD_ID:
			break;

	}
}

CAN::CANOpenNMT * CAN::CANOpen::nmt()
{
	if (!_map_nmt)
	{
		_map_nmt = new CAN::CANOpenNMT(_node_id, this);
	}
	
	return _map_nmt;
}

CAN::CANOpenEMCY * CAN::CANOpen::emergency()
{
	if (!_map_emergency)
	{
		_map_emergency = new CAN::CANOpenEMCY(_node_id, this);
	}
	
	return _map_emergency;
}

CAN::CANOpenSYNC * CAN::CANOpen::sync()
{
	if (!_map_sync)
	{
		_map_sync = new CAN::CANOpenSYNC(this);
	}
	
	return _map_sync;
}

CAN::CANOpenSDO * CAN::CANOpen::sdo()
{
	if (!_map_sdo)
	{
		_map_sdo = new CAN::CANOpenSDO(_node_id, this);
	}

	return _map_sdo;
}

CAN::CANOpenPDO * CAN::CANOpen::pdo(uint8_t pdo_id)
{
	uint8_t fct = pdo_id;
	switch (pdo_id)
	{
		case PDO1_ID_RX:
		case PDO1_ID_TX:
			fct = 3;
			break;

		case PDO2_ID_RX:
		case PDO2_ID_TX:
			fct = 5;
			break;

		case PDO3_ID_RX:
		case PDO3_ID_TX:
			fct = 7;
			break;

		case PDO4_ID_RX:
		case PDO4_ID_TX:
			fct = 9;
			break;
	}

	std::map < uint8_t, CANOpenPDO * >::iterator it = _map_pdo.find(fct);
	if (it == _map_pdo.end())
	{
		_map_pdo[fct] = new CANOpenPDO(fct, _node_id, this);
	}

	return _map_pdo[fct];
}

int32_t CAN::CANOpen::writeData(CAN::CANOpenBuffer * buffer)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "writeData");

	// {
		// std::stringstream ss;
		// uint8_t data[8];
		// int32_t len = buffer->read(data, 8);
		// ss << "writeData out (" << len << ") :" << std::endl;
		// ss << std::hex;
		// ss << " pdo_id = 0x" << std::setfill('0') << std::setw(2) << (int)buffer->pdo_id << std::endl;
		// ss << " node_id = 0x" << std::setfill('0') << std::setw(2) << (int)buffer->node_id << std::endl;
		// for (int32_t i=0; i<len; ++i)
		// {
			// ss << " 0x" << std::setfill('0') << std::setw(2) << (int)data[i];
		// }
		// ss << std::dec << std::endl;
		// Log::getLogger()->info(__FILE__, __LINE__, ss.str());
	// }

	CAN::CANBuffer buf;
	
	// conversion de CANOpenBuffer vers CANBuffer
	buffer->toCANBuffer(&buf);
	
	// ecriture sur le bus CAN
	int32_t len = _bus_can->writeData(&buf);

	// creation du FIFO de lecture
	CANOpenFifo * fifo = 0;
	std::map < uint8_t, CANOpenFifo * >::iterator it = _map_fifo.find(buffer->pdo_id - 1);
	if (it == _map_fifo.end())
	{
		fifo = new CANOpenFifo();
		_map_fifo[buffer->pdo_id - 1] = fifo;
	}
	
	return len;
}

int32_t CAN::CANOpen::readData(CAN::CANOpenBuffer * buffer)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "readData");

	std::map < uint8_t, CANOpenFifo * >::iterator it = _map_fifo.find(buffer->pdo_id);
	if (it == _map_fifo.end())
	{
		throw CANOpenException(__FILE__, __LINE__, "fifo vide.");
	}

	CANOpenFifo * fifo = it->second;
	CAN::CANOpenBuffer * buf = fifo->firstOut();
	uint8_t data[8];
	int32_t len = buf->read(data, 8);
	buffer->write(data, len);
	delete buf;
	return len;
}

int32_t CAN::CANOpen::actionIn()
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t data[512];
	int32_t length = 512;
	if (_bus_can->actionIn(data, length) > 0)
	{
		CAN::CANBuffer buf;
		int32_t len = _bus_can->readData(&buf);

		CAN::CANOpenBuffer * buffer = new CAN::CANOpenBuffer();
		buffer->fromCANBuffer(&buf);

		switch(buffer->pdo_id)
		{
			case MNT_ID:
			{
				// impossible : inuquement en reception
			}
			break;

			case EMGY_ID:
			{
				uint8_t data[8];
				int32_t len = buffer->read(data, 8);
				uint8_t node_id = data[1];
				if (node_id == 0)
				{
					// message SYNC
				}
				else
				{
					// message EMCY
				}
			}
			break;

			case GUARD_ID:
			{
				if (buffer->node_id == _node_id)
				{
					uint8_t data[8];
					int32_t len = buffer->read(data, 8);
					if (len)
					{
						// _state_machine = data[0] & 0x7F;
					}
				}
			}
			break;

			case PDO1_ID_RX:
			case PDO1_ID_TX:
			case PDO2_ID_RX:
			case PDO2_ID_TX:
			case PDO3_ID_RX:
			case PDO3_ID_TX:
			case PDO4_ID_RX:
			case PDO4_ID_TX:
			case SDO_ID_RX:
			case SDO_ID_TX:
			{
				if (buffer->node_id == _node_id)
				{
					// mise en fifo
					CANOpenFifo * fifo = 0;
					std::map < uint8_t, CANOpenFifo * >::iterator it = _map_fifo.find(buffer->pdo_id);
					if (it == _map_fifo.end())
					{
						fifo = new CANOpenFifo();
						_map_fifo[buffer->pdo_id] = fifo;
					}
					else
					{
						fifo = it->second;
					}

					fifo->lastIn(buffer);
				}
			}
			break;

			default:
			{
				delete buffer;
			}
			break;
		}

		return len;
	}

	return 0;
}

int32_t CAN::CANOpen::actionOut()
{
	return 0;
}

int32_t CAN::CANOpen::actionError()
{
	return 0;
}
