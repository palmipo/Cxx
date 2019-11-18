#include "canopenemcy.h"
#include "canopen.h"
#include "canopenbuffer.h"

CAN::CANOpenEMCY::CANOpenEMCY(uint8_t node_id, CAN::CANOpen * interface_can)
//: CAN::CANOpenFifo()
: _node_id(node_id)
, _bus_can(interface_can)
{}

int32_t CAN::CANOpenEMCY::read(uint16_t * err_code, uint8_t * err_register, uint8_t * vendor_specific_data, int32_t length)
{
	CANOpenBuffer buffer;// = firstOut();
	_bus_can->readData(&buffer);
	
	int32_t i=0;
	int32_t cpt = 0;
	uint8_t data[8];
	int32_t len = buffer.read(data, 8);
	if (len)
	{
		*err_code = data[cpt]; cpt += 1;
		*err_code |= data[cpt] << 8; cpt += 1;
		*err_register = data[cpt]; cpt += 1;

		for (i=0; ((i<length) && (cpt<len)); ++i, ++cpt)
		{
			vendor_specific_data[i] = data[cpt];
		}
	}
	
	return i;
}

int32_t CAN::CANOpenEMCY::write(uint8_t arg_1, uint8_t arg_2, uint8_t arg_3, uint8_t arg_4, uint8_t arg_5, uint8_t arg_6, uint8_t arg_7, uint8_t arg_8)
{
	uint8_t data[8];
	data[0] = arg_1;
	data[1] = arg_2;
	data[2] = arg_3;
	data[3] = arg_4;
	data[4] = arg_5;
	data[5] = arg_6;
	data[6] = arg_7;
	data[7] = arg_8;


	CANOpenBuffer buffer;
	buffer.write(data, 8);
	buffer.pdo_id = EMGY_ID;
	buffer.node_id = _node_id;
	
	_bus_can->writeData(&buffer);
}
