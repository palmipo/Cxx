#include "modbusfactory.h"
#include "modbuschannel.h"
#include "modbusmsgfc03.h"
#include "modbusmsgfc06.h"
#include "modbusexception.h"
#include "modbusmsgexception.h"
#include "pollexception.h"
#include "rs232exception.h"
#include "log.h"
#include <thread>

static void scrute(Modbus::ModbusFactory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(1000, 1, 1, 1);
	}
}

int main(int argc, char ** argv)
{
	int32_t fin = 0;
	Modbus::ModbusFactory factory;
	std::thread t(scrute, &factory, &fin);

	try
	{
		Modbus::ModbusChannel * channel = factory.rtu(argv[1], 19200, 1, 1);
		//~ Modbus::ModbusChannel * channel = factory.tcp(argv[1]);

		{
			/* FWST a RDY ? */
			Modbus::ModbusMsgFC03 msg;
			msg.setSlaveAddress(2);
			msg.setRegisterAddr(0xFFDB, 1);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
			if (msg.slaveAddress() != 2)
			{
				Log::getLogger()->debug(__FILE__, __LINE__, "erreur reception Modbus !");
			}
			if (0x3 != msg.getRegister(0xFFDB))
			{
				Log::getLogger()->debug(__FILE__, __LINE__, "erreur drive mauvais mode !");
			}
			Log::getLogger()->debug(__FILE__, __LINE__, "reception Modbus !");
		}
	
		{
			/* MODE a TP */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0x5DC, 0x5450);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
		}
		
		{
			/* FWCD a APPLY */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0xFFDA, 0x2);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
		}

		{
			/* FWST a SUCCED ? */
			Modbus::ModbusMsgFC03 msg;
			msg.setSlaveAddress(2);
			msg.setRegisterAddr(0xFFDB, 1);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
			if (0x5 != msg.getRegister(0xFFDB))
			{
				Log::getLogger()->debug(__FILE__, __LINE__, "erreur drive mauvais mode !");
			}
		}

		{
			/* MODE a TP */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0x5DC, 0x5450);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
		}
	
		{
			/* FWCD a APPLY */
			Modbus::ModbusMsgFC06 msg;
			msg.setSlaveAddress(2);
			msg.setRegister(0xFFDA, 0x3);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
		}

		{
			/* FWST a SUCCED ? */
			Modbus::ModbusMsgFC03 msg;
			msg.setSlaveAddress(2);
			msg.setRegisterAddr(0xFFDB, 1);
			msg.encodeQuestion();
			channel->sendFC(&msg);
			msg.decodeResponse();
			if (0x4 != msg.getRegister(0xFFDB))
			{
				Log::getLogger()->debug(__FILE__, __LINE__, "erreur drive mauvais mode !");
			}
		}
	}
	catch(RS232Exception e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(Modbus::ModbusMsgException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(Modbus::ModbusException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(PollException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exeption");
	}

	t.join();
	return 0;
}
