#include "canopennmt.h"
#include "canopen.h"
#include "canopenpdo.h"
#include "canopenbuffer.h"
#include <thread>


bool _fin_thread = false;
void threadPDO(CAN::CANOpenPDO * pdo)
{
	int32_t period = pdo->cyclic();
	while (!_fin_thread)
	{
		pdo->send();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

CAN::CANOpenNMT::CANOpenNMT(uint8_t node_id, CAN::CANOpen * interface_can)
: _node_id(node_id)
, _bus_can(interface_can)
{}

int32_t CAN::CANOpenNMT::command(uint8_t cmd)
{
	CAN::CANOpenBuffer buffer;
	buffer.pdo_id = 0;
	buffer.node_id = 0;

	uint8_t data[2];
	data[0] = cmd;
	data[1] = _node_id;
	buffer.write(data, 2);

	return _bus_can->writeData(&buffer);
}

int32_t CAN::CANOpenNMT::start()
{
	command(0x01);

	_fin_thread = false;
	uint8_t tabPdo[] = { 3, 5, 7 };

	for (int32_t i=0; i<3; ++i)
	{
		CAN::CANOpenPDO * pdo = _bus_can->pdo(tabPdo[i]);

		if (pdo->cyclic() != 0)
		{
			_thread[i] = new std::thread(threadPDO, pdo);
			_thread[i]->detach();
		}
	}
}

int32_t CAN::CANOpenNMT::stop()
{
	_fin_thread = true;

	return command(0x02);
}

int32_t CAN::CANOpenNMT::preOperational()
{
	_fin_thread = true;

	return command(0x80);
}

int32_t CAN::CANOpenNMT::reset()
{
	_fin_thread = true;

	return command(0x81);
}

int32_t CAN::CANOpenNMT::resetCommunication()
{
	_fin_thread = true;

	return command(0x82);
}
