#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "raspiuart.h"
#include "modbusexception.h"
#include "modbusmsgheader.h"
#include "modbusrtu.h"
#include "r4d3b16.h"
#include "n4dih32.h"
#include "r4dcb08.h"
#include "tempo.h"
#include "log.h"
#include <cstdint>
#include <sstream>
#include <iostream>
#include <thread>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << std::string(argv[0]) << " </dev/ttyUSB0>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	try
	{
		RS232Factory uart_factory;
		RS232 * serial = uart_factory.add(argv[1]);
		serial->setConfig(B9600, 8, 'N', 1);

		RaspiUart uart(serial);

		Modbus::ModbusRtu rtu(&uart);

		Modbus::R4D3B16 msg_out(4, &rtu);
		//~ msg_out.closeAll();
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//~ msg_out.openAll();
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//~ msg_out.toggle(1);
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//~ msg_out.open(2);
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//~ msg_out.close(3);
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//~ std::cout << (int)msg_out.get(4) << std::endl;
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(100));

		Modbus::N4DIH32 msg_in(0x08, &rtu);
		//~ msg_in.resetFactory();
		//~ msg_in.getAll();
		//~ msg_in.setTempoAutomaticReporting(1);
		//~ msg_in.setAllAutomaticReporting(0);
		//~ std::this_thread::sleep_for(std::chrono::seconds(10));
		//~ msg_in.setAutomaticReporting(1, 0);


		//~ Modbus::R4DCB08 msg_brd(0xff, &rtu);
		//~ msg_brd.moduleAddress();
		//~ msg_brd.setModuleAddress(1);
		// std::this_thread::sleep_for(std::chrono::seconds(10));

		Modbus::R4DCB08 msg_temp(1, &rtu);
		//~ msg_temp.resertFactory();
		//~ msg_temp.temperature(0);
		msg_temp.allTemperature();
		//~ msg_temp.moduleAddress();
		//~ msg_temp.setAutomaticTemperatureReport(1);
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(500));

		//~ std::this_thread::sleep_for(std::chrono::minutes(1));
		//~ msg_out.closeAll();
		//~ msg_in.setTempoAutomaticReporting(0);
		//~ msg_brd.setAutomaticTemperatureReport(0);
		//~ msg_temp.setAutomaticTemperatureReport(0);

		Tempo::secondes(10);

		return 0;
	}
	catch(Modbus::ModbusException e)
	{
		std::stringstream ss;
		ss << "ModbusException : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}
	catch(...)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "exception ...");
		return -1;
	}
}
