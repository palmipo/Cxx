#include "modbusmsgfc43.h"
#include "modbuschannel.h"
#include <iostream>
#include <iomanip>
#include <cstring>

uint16_t Modbus::ModbusMsgFC43::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encodeHeader();

	data[cpt] = mei_type;
	cpt += 1;
	
	data[cpt] = device_id;
	cpt += 1;
	
	data[cpt] = object_id;
	cpt += 1;

	return cpt;
}
uint16_t Modbus::ModbusMsgFC43::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeHeader();

	mei_type = data[cpt];
	cpt += 1;

	device_id = data[cpt];
	cpt += 1;

	object_id = data[cpt];
	cpt += 1;
	

	return cpt;
}

uint16_t Modbus::ModbusMsgFC43::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeHeader();

	{
		mei_type = data[cpt];
		cpt += 1;

		device_id = data[cpt];
		cpt += 1;

		conformity_level = data[cpt];
		cpt += 1;

		more_follow = data[cpt];
		cpt += 1;

		next_object_id = data[cpt];
		cpt += 1;

		nb_object = data[cpt];
		cpt += 1;
		
		for (uint8_t i=0; i<nb_object; i+=1)
		{
			object[i].object_id = data[cpt];
			cpt += 1;

			object[i].object_length = data[cpt];
			cpt += 1;
			
			::memcpy(object[i].object_value, data+cpt, object[i].object_length);
			cpt += object[i].object_length;
		}
	}

	return cpt;
}
