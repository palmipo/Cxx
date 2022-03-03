#include "modbuschannel.h"
#include "polldevice.h"

Modbus::ModbusChannel::ModbusChannel(PollDevice * device)
: _device(device)
{}

