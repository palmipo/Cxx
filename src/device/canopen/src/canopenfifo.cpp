#include "canopenfifo.h"
#include "log.h"
#include "canopenexception.h"
#include <cstdint>
#include <sstream>
#include <thread>

CAN::CANOpenFifo::CANOpenFifo()
{}

CAN::CANOpenFifo::~CANOpenFifo()
{
	while (!_fifo.empty())
	{
		delete _fifo.front();
		_fifo.pop();
	}
}

void CAN::CANOpenFifo::lastIn(CANOpenBuffer * buffer)
{
	_fifo.push(buffer);
}

CAN::CANOpenBuffer * CAN::CANOpenFifo::firstOut(int32_t max_retry, int32_t timeout)
{
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}

	if (_fifo.empty())
	{
		throw CANOpenException(__FILE__, __LINE__, "fifo vide !");
	}
	
	CANOpenBuffer * buffer = _fifo.front();
	_fifo.pop();
	return buffer;
}
