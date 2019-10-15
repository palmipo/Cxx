#include "modbusfactory.h"
#include "modbuschannel.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include "log.h"
#include <thread>

static void scrute(Modbus::ModbusFactory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(1000);
	}
}

int main(int argc, char ** argv)
{
	try{
		int32_t fin = 0;
		Modbus::ModbusFactory factory;
		std::thread t(scrute, &factory, &fin);

		Modbus::ModbusChannel * channel = factory.rtu(argv[1], 19200, 1, 1);

		{
			/* FWST a RDY ? */
			Modbus::ModbusMsgFC03 msg;
			msg.setSlaveAddress(2);
			msg.setRegisterAddr(0xFFDB, 1);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
			if (0x3 != msg.getRegister(0xFFDB))
			{
				return -1;
			}
		}
	
		{
			/* MODE a TP */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0x5DC, 0x5450);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
		}
		
		{
			/* FWCD a APPLY */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0xFFDA, 0x2);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
		}

		{
			/* FWST a SUCCED ? */
			Modbus::ModbusMsgFC03 msg;
			msg.setSlaveAddress(2);
			msg.setRegisterAddr(0xFFDB, 1);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
			if (0x5 != msg.getRegister(0xFFDB))
			{
				return -1;
			}
		}

		{
			/* MODE a TP */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0x5DC, 0x5450);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
		}
	
		{
			/* FWCD a APPLY */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0xFFDA, 0x3);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
		}

		{
			/* FWST a SUCCED ? */
			Modbus::ModbusMsgFC03 msg;
			msg.setSlaveAddress(2);
			msg.setRegisterAddr(0xFFDB, 1);
			channel->sendFC(&msg);
			channel->recvFC(&msg);
			if (0x4 != msg.getRegister(0xFFDB))
			{
				return -1;
			}
		}

		fin = 1;
		return 0;
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exeption");
		return -1;
	}
}