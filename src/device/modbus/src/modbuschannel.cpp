#include "modbuschannel.h"
#include "modbusmsg.h"
#include "polldevice.h"

Modbus::ModbusChannel::ModbusChannel(PollDevice * device)
: _device(device)
{}
