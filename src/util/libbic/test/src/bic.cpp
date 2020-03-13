// #include "libbic/interface.h"
#include "libbic/factory.h"
#include "libbic/ctrl.h"
#include "libbic/ctrlconfig.h"
#include "libbic/ctrlconfigip.h"
#include "libbic/ctrlconfigserial.h"
#include "libbic/element.h"
#include "libbic/drive.h"
#include "libbic/modbus.h"
#include "libbic/canbus.h"
#include "libbic/power.h"
#include "libbic/plc.h"
#include "libbic/signal.h"
#include "libbic/index.h"
#include "libbic/command.h"
#include "libbic/cmdmodbus.h"
#include "libbic/exception.h"
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		BIC::Factory::getInstance()->readConfigFile(argv[1]);

		BIC::Drive * drive = BIC::Factory::getInstance()->find_drive("ATV630_2");
		
		BIC::Power * power = drive->getPower();
		BIC::Plc * plc = BIC::Factory::getInstance()->find_plc(power->str_plc_id);
		BIC::Modbus * modbus_plc = plc->getModbus(power->str_modbus_iface);
		BIC::Signal * signal_on_off = plc->find_signal(power->str_signal_id);
		BIC::Index * index_on_off = signal_on_off->find_index(power->str_index_id);
		BIC::CommandModbus * cmd_modbus = (BIC::CommandModbus *)index_on_off->find_cmd("modbus");

		BIC::Modbus * modbus = drive->getModbus("RTU");
		std::cout << "RTU str_ctrl_id : " << modbus->str_ctrl_id << std::endl;

		BIC::Ctrl * ctrl = BIC::Factory::getInstance()->find_ctrl(modbus->str_ctrl_id);
		std::cout << "str_type : " << ctrl->str_type << std::endl;
		BIC::CtrlConfig * cfg = ctrl->getCfg();
		
		BIC::CtrlConfigSerial * serial = (BIC::CtrlConfigSerial *)cfg->getCtrl();
		std::cout << "str_iface : " << serial->str_iface << std::endl;
		std::cout << "str_device : " << serial->str_device << std::endl;
		
		// BIC::CtrlConfigIp * ip = (BIC::CtrlConfigIp *)cfg->getCtrl();
		// std::cout << "str_iface : " << ip->str_iface << std::endl;
		// std::cout << "str_address : " << ip->elem_address->str_value << std::endl;

		BIC::Canbus * canbus = drive->getCanbus("CAN");
		std::cout << "str_ctrl_id : " << canbus->str_ctrl_id << std::endl;

		delete BIC::Factory::getInstance();
	}
	catch(BIC::Exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "erreur ..." << std::endl;
	}

	return 0;
}
