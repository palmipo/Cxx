#include "canopenstatemachineinit.h"
#include "canopen.h"
#include "canopenpdo.h"
#include "canopenbuffer.h"
#include "canopenexception.h"

bool _fin_thread = false;

CAN::CANOpenStateMachine::CANOpenStateMachine(uint8_t node_id, CAN::CANOpen * interface_can)
: _internal_state(Initialization)
, _node_id(node_id)
, _bus_can(interface_can)
{}

void threadPDO(CAN::CANOpenPDO * pdo)
{
	int32_t period = pdo->cyclic();
	while (!_fin_thread)
	{
		//~ pdo->write();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void CAN::CANOpenStateMachine::start()
{
	if ((_internal_state == PreOperational) || (_internal_state == Stopped))
	{
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
		_internal_state = Operational;
	}
	
	throw CANOpenException(__FILE__, __LINE__, "change state erreur");
}

void CAN::CANOpenStateMachine::stop()
{
	if ((_internal_state == PreOperational) || (_internal_state == Operational))
	{
		_fin_thread = true;
		_internal_state = Stopped;
	}
	
	throw CANOpenException(__FILE__, __LINE__, "change state erreur");
}

void CAN::CANOpenStateMachine::preOperational()
{
	if ((_internal_state == Initialization) || (_internal_state == Operational) || (_internal_state == Stopped))
	{
		_fin_thread = true;
		
		// send boot-up message

		_internal_state = PreOperational;
	}
	
	throw CANOpenException(__FILE__, __LINE__, "change state erreur");
}

void CAN::CANOpenStateMachine::reset()
{
	_fin_thread = true;
	_internal_state = Initialization;
}

void CAN::CANOpenStateMachine::resetCommunication()
{
	_fin_thread = true;
	_internal_state = Initialization;
}
