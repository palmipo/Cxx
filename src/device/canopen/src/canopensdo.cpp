#include "canopensdo.h"
#include "canopenexception.h"
#include "canopen.h"
#include "log.h"
#include <thread>
#include <sstream>
#include <iomanip>
extern int32_t scrute_timeout;

CAN::CANOpenSDO::CANOpenSDO(uint8_t node_id, CAN::CANOpen * interface_can)
: _node_id(node_id)
, _bus_can(interface_can)
{}

int32_t CAN::CANOpenSDO::writeDictionary(uint16_t index, uint8_t subindex, uint8_t * data, int32_t data_length)
{
	// std::stringstream ss_log;
	// ss_log << data_length;
	// Log::getLogger()->DEBUG(__FILE__, __LINE__, ss_log.str());
	int32_t len = 0;
	int32_t data_offset = 0;
	if (data_length > 4)
	{
		CANOpenSdoBuffer buffer_snd;
		buffer_snd.pdo_id = SDO_ID_TX;
		buffer_snd.node_id = _node_id;
		buffer_snd.command = (0x1 << 5) | 0x1;
		buffer_snd.index = index;
		buffer_snd.subindex = subindex;
		buffer_snd.write((uint8_t*)&data_length, 4);

		// emission
		CANOpenBuffer buffer;
		buffer_snd.toCANOpenBuffer(&buffer);
		_bus_can->writeData(&buffer);

		// reponse
		buffer.pdo_id = SDO_ID_RX;
		_bus_can->readData(&buffer);
		CANOpenSdoBuffer buffer_rcv;
		buffer_rcv.fromCANOpenBuffer(&buffer);

		// erreur
		if (buffer_rcv.command & 0x80)
		{
			error(buffer_rcv);
		}
		
		uint8_t toggle = 0;
		while (data_offset < data_length)
		{
			int32_t cpt = 0;
			uint8_t msg[8];
			msg[cpt] = (0x3 << 5) | (toggle << 4); cpt += 1;
			toggle = (toggle + 1) % 2;
			for (; ((cpt<8) && (data_offset<data_length)); ++data_offset, ++cpt)
			{
				// msg[7 - cpt] = data[data_offset];
				msg[cpt] = data[data_offset];
			}

			// emission
			buffer.pdo_id = SDO_ID_TX;
			buffer.node_id = _node_id;
			buffer.write(msg, 8);
			_bus_can->writeData(&buffer);

			// reponse
			buffer.pdo_id = SDO_ID_RX;
			_bus_can->readData(&buffer);
			len += buffer_rcv.fromCANOpenBuffer(&buffer);

			// erreur
			if (buffer_rcv.command & 0x80)
			{
				error(buffer_rcv);
			}
		}
	}
	else
	{
		CANOpenSdoBuffer buffer_snd;
		buffer_snd.pdo_id = SDO_ID_TX;
		buffer_snd.node_id = _node_id;
		buffer_snd.command = (0x1 << 5) | ((4 - data_length) & 0x3) << 2 | 0x3;
		buffer_snd.index = index;
		buffer_snd.subindex = subindex;
		buffer_snd.write(data, data_length);

		// emission
		CANOpenBuffer buffer;
		buffer_snd.toCANOpenBuffer(&buffer);
		_bus_can->writeData(&buffer);

		// reponse
		buffer.pdo_id = SDO_ID_RX;
		_bus_can->readData(&buffer);
		CANOpenSdoBuffer buffer_rcv;
		len += buffer_rcv.fromCANOpenBuffer(&buffer);

		// erreur
		if (buffer_rcv.command & 0x80)
		{
			error(buffer_rcv);
		}
	}

	return len;
}

int32_t CAN::CANOpenSDO::readDictionary(uint16_t index, uint8_t subindex, uint8_t * data_rcv, int32_t data_rcv_length)
{
	CANOpenSdoBuffer buffer_snd;
	buffer_snd.pdo_id = SDO_ID_TX;
	buffer_snd.node_id = _node_id;
	buffer_snd.command = (0x2 << 5);
	buffer_snd.index = index;
	buffer_snd.subindex = subindex;

	// emission
	CANOpenBuffer buffer;
	buffer_snd.toCANOpenBuffer(&buffer);
	_bus_can->writeData(&buffer);

	// reponse
	buffer.pdo_id = SDO_ID_RX;
	_bus_can->readData(&buffer);
	CANOpenSdoBuffer buffer_rcv;
	buffer_rcv.fromCANOpenBuffer(&buffer);

	// erreur
	if (buffer_rcv.command & 0x80)
	{
		error(buffer_rcv);
	}

	int32_t data_offset = 0;
	if (buffer_rcv.command & 0x1)
	{
		if (buffer_rcv.command & 0x2)
		{
			// read dictionary
			uint32_t data_size = 4 - ((buffer_rcv.command >> 2) & 0x3);
			
			uint8_t data[data_size];
			int32_t len = buffer_rcv.read(data, data_size);
			for (int32_t i=0; ((i<len) && (data_offset<data_rcv_length)); ++i, ++data_offset)
			{
				data_rcv[data_offset] = data[len - i - 1];
			}
		}
		else
		{
			// read dictionary segmented
			int32_t data_size = 0;
			buffer_rcv.read((uint8_t*)&data_size, 4);
			
			bool fin = false;
			uint8_t toggle = 0;
			while (!fin)
			{
				// demande du paquet suivant
				buffer_snd.pdo_id = SDO_ID_TX;
				buffer_snd.node_id = _node_id;
				buffer_snd.command = (0x3 << 5) | (toggle << 4) | 1;
				buffer_snd.index = index;
				buffer_snd.subindex = subindex;
				toggle = (toggle + 1) % 2;

				// emission
				buffer_snd.toCANOpenBuffer(&buffer);
				_bus_can->writeData(&buffer);

				// reponse
				buffer.pdo_id = SDO_ID_RX;
				_bus_can->readData(&buffer);
				buffer_rcv.fromCANOpenBuffer(&buffer);

				// erreur
				if (buffer_rcv.command & 0x80)
				{
					error(buffer_rcv);
				}
				
				// lecture du paquet suivant
				int32_t taille = 8;
				if (buffer_rcv.command & 1)
				{
					taille = 8 - ((buffer_rcv.command >> 1) & 0x07);
					fin = true;
				}

				uint8_t tmp[taille];
				int32_t len = buffer.read(tmp, taille);
				//!\ ne pas prendre le 1er octet (buffer_rcv.command)
				for (int32_t i=1; ((i<len) && (data_offset<data_rcv_length)); ++i, ++data_offset)
				{
					// data_rcv[data_offset] = tmp[len - i - 1];
					data_rcv[data_offset] = tmp[i];
				}
			}
		}
	}

	return data_offset;
}


int32_t CAN::CANOpenSDO::abort(uint16_t index, uint8_t subindex, uint8_t err_class, uint8_t err_code, uint16_t additional_info)
{
	CANOpenSdoBuffer buffer_snd;
	buffer_snd.pdo_id = SDO_ID_TX;
	buffer_snd.node_id = _node_id;
	buffer_snd.command = 0x80;
	buffer_snd.index = index;
	buffer_snd.subindex = subindex;
	
	int32_t cpt = 0;
	uint8_t data[4];
	data[cpt] = (additional_info & 0x00FF); cpt += 1;
	data[cpt] = (additional_info & 0xFF00) >> 8; cpt += 1;
	data[cpt] = err_code; cpt += 1;
	data[cpt] = err_class; cpt += 1;
	buffer_snd.write(data, cpt);

	// emission
	CANOpenBuffer buffer;
	buffer_snd.toCANOpenBuffer(&buffer);
	int32_t len = _bus_can->writeData(&buffer);

	return len;
}

void CAN::CANOpenSDO::error(CANOpenSdoBuffer buffer_rcv)
{
	int32_t cpt = 0;
	uint8_t err[4];
	buffer_rcv.read(err, 4);
	uint16_t additional_info = err[cpt]; cpt += 1;
	additional_info |= err[cpt] << 8; cpt += 1;
	uint8_t err_code = err[cpt]; cpt += 1;
	uint8_t err_class = err[cpt]; cpt += 1;

	std::stringstream ss;
	ss << "error class : " << (int)err_class;
	ss << " code : " << (int)err_code;
	ss << " additional info : " << additional_info;
	throw CAN::CANOpenException(__FILE__, __LINE__, ss.str().c_str());
}

// int32_t CAN::CANOpenSDO::actionIn(uint8_t * data, int32_t len)
// {
	// return _bus_can->actionIn(data, len);
// }

// int32_t CAN::CANOpenSDO::actionOut(uint8_t * data, int32_t len)
// {
	// return _bus_can->actionOut(data, len);
// }

// int32_t CAN::CANOpenSDO::actionError(uint8_t * data, int32_t len)
// {
	// return _bus_can->actionError(data, len);
// }

// void CAN::CANOpenSDO::close()
// {
	// _bus_can->close();
// }
