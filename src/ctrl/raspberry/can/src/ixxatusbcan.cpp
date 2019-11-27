#include "ixxatusbcan.h"
#include "canbuffer.h"
#include "canexception.h"
#include <sys/ioctl.h>
#include <net/if.h>
#if defined __MINGW64__ || defined __MINGW32__ || defined __CYGWIN__
#else
	#include <linux/sockios.h>
	#include <linux/can.h>
	#include <linux/can/raw.h>
#endif
// #include <thread>
#include <cerrno>
#include <cstring>
#include <unistd.h>

/* constructeur socket client */
Ixxat::UsbCan::UsbCan(uint16_t cob_id, PollDevice * device)
: CAN::Bus(cob_id, device)
{}

Ixxat::UsbCan::~UsbCan()
{}

int32_t Ixxat::UsbCan::writeData(uint16_t node_id, uint8_t * msg, int32_t length)
{
#if defined __MINGW64__ || defined __MINGW32__ || defined __CYGWIN__
#else
	struct can_frame frame;
	::memset(&frame, 0x0, sizeof(frame));

	/* first fill, then send the CAN frame */
	frame.can_id = node_id;
	::memcpy((char *)frame.data, msg, length);
	frame.can_dlc = length;

	int32_t len = _device->write((uint8_t*)&frame, sizeof(frame));
	if (len < 0)
	{
		throw CAN::Exception(__FILE__, __LINE__, errno);
	}

	return len;
#endif
}

int32_t Ixxat::UsbCan::readData(uint16_t * node_id, uint8_t * data, int32_t data_length, int32_t max_retry, int32_t timeout)
{
	if (_fifo.empty())
	{
		throw CAN::Exception(__FILE__, __LINE__, "fifo vide");
	}
	
	CAN::CANBuffer * buffer = _fifo.front();
	_fifo.pop();
	
	*node_id = buffer->cob_id;
	int32_t len = buffer->read(data, data_length);

	return len;
}

int32_t Ixxat::UsbCan::write(uint8_t * data, int32_t len)
{
	return _device->write(data, len);
}

int32_t Ixxat::UsbCan::read(uint8_t * data, int32_t len)
{
	return _device->read(data, len);
}

int32_t Ixxat::UsbCan::actionError()
{
	return 0;
}

int32_t Ixxat::UsbCan::actionIn()
{
#if defined __MINGW64__ || defined __MINGW32__ || defined __CYGWIN__
#else
	struct can_frame frame;
	_device->read(&frame, sizeof(struct can_frame));

	CAN::CANBuffer * buffer = new CAN::CANBuffer();
	buffer->cob_id = frame.can_id;
	buffer->write(frame.data, frame.can_dlc);
	_fifo.push(buffer);

	len = frame.can_dlc;

	return len;
#endif
}

int32_t Ixxat::UsbCan::actionOut()
{
	return 0;
}
