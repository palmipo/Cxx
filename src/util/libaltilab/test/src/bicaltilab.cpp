#include "libbic/factory.h"
#include "libbic/ctrl.h"
#include "libbic/ctrlconfig.h"
#include "libbic/ctrlconfigip.h"
#include "libbic/ctrlconfigserial.h"
#include "libbic/element.h"
#include "libbic/drive.h"
#include "libbic/modbus.h"
#include "libbic/canbus.h"
#include "libbic/exception.h"
#include "libaltilab/altilab.h"
#include "modbusfactory.h"
#include "modbustcp.h"
#include "modbusmsgfc06.h"
#include "modbusexception.h"
#include "log.h"
#include <iostream>
#include <sstream>
#include <thread>


void thread_poll_start(Modbus::ModbusFactory * factory, int32_t * fin)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "DEBUT thread_poll_start");

	while (! *fin)
	{
		factory->scrute(1000, 1, 1, 1);
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "FIN thread_poll_start");
}

void thread_action_start(Modbus::ModbusFactory * factory, int32_t * fin)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "DEBUT thread_action_start");

	while(! *fin)
	{
		try
		{
			factory->actionOut();
			factory->actionIn();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		catch(Modbus::ModbusException e)
		{
			std::stringstream ss;
			ss << "thread_action_start exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(PollException e)
		{
			std::stringstream ss;
			ss << "thread_action_start exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(...)
		{
			Log::getLogger()->debug(__FILE__, __LINE__, "thread_action_start exception");
		}
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "FIN thread_action_start");
}

int main(int argc, char ** argv)
{
	int32_t fin = 0;
	Modbus::ModbusFactory factory;
	std::thread t1(thread_poll_start, &factory, &fin);
	std::thread t2(thread_action_start, &factory, &fin);

	try
	{
		BIC::Factory::getInstance()->readConfigFile(argv[1]);

		BIC::Drive * bic_drive = BIC::Factory::getInstance()->find_drive("ATV630_1");
		
		// BIC::Modbus * bic_modbus = bic_drive->getModbus("TCP");
		BIC::Modbus * bic_modbus = bic_drive->getModbus("RTU");
		std::cout << "str_ctrl_id : " << bic_modbus->str_ctrl_id << std::endl;
		
		BIC::Ctrl * bic_ctrl = BIC::Factory::getInstance()->find_ctrl(bic_modbus->str_ctrl_id);
		std::cout << "str_type : " << bic_ctrl->str_type << std::endl;
		
		BIC::CtrlConfig * bic_cfg = bic_ctrl->getCfg();
		
		BIC::CtrlConfigBase * bic_base = bic_cfg->getCtrl();

		AltiLab::Parser altilab_parser(bic_modbus->str_config_xml);
		AltiLab::DataObjectCollection * altilab_doc = altilab_parser.dataObject();

		if (bic_cfg->getCtrl()->str_iface == "ethernet")
		{
			BIC::CtrlConfigIp * bic_ip = (BIC::CtrlConfigIp *)bic_base;

			Modbus::ModbusChannel * modbus_tcp = factory.tcp(bic_ip->elem_address->str_value);

			// IM00 = DHCP
			AltiLab::DataObject * IM00_dataobject = altilab_doc->find_dataobject(bic_ip->elem_mode->str_register); // IM00
			AltiLab::DataObjectItem * IM00_address_item = IM00_dataobject->find_dataobjectitem("address");
			std::cout << "IM00_address_item : " << IM00_address_item->str_value << std::endl;
			std::cout << "IM00_address_item : " << IM00_address_item->str_type << std::endl;

			if (IM00_address_item->str_type == "modbus")
			{
				AltiLab::DataObjectItem * IM00_choicetype_item = IM00_dataobject->find_dataobjectitem("choicetype");
				AltiLab::ChoiceType * IM00_choicetype = altilab_doc->find_choicetype(IM00_choicetype_item->str_value);
				AltiLab::Choice * IM00_choice = IM00_choicetype->find_choice(bic_ip->elem_mode->str_value); // DHCP
				std::cout << "IM00_choice : " << IM00_choice->str_value << std::endl;

				Modbus::ModbusMsgFC06 IM00_msg;
				IM00_msg.setSlaveAddress(std::strtoul(bic_modbus->str_slave_address.c_str(), 0, 0));
				IM00_msg.setRegister(std::strtoul(IM00_address_item->str_value.c_str(), 0, 0), std::strtoul(IM00_choice->str_value.c_str(), 0, 0));
				modbus_tcp->sendFC(&IM00_msg);

				// AltiLab::DataObjectItem * IM00_modifiable_item = IM00_dataobject->find_dataobjectitem("modifiable");
				// std::cout << "IM00_modifiable_item : " << IM00_modifiable_item->str_value << std::endl;
				// if (IM00_modifiable_item->str_value == "gatingOff")
				// {
					/* CMI = 2 */
					// AltiLab::DataObject * CMI_dataobject = doc->find_dataobject("CMI");
					// AltiLab::DataObjectItem * CMI_address_item = CMI_dataobject->find_dataobjectitem("address");
					// std::cout << "CMI_address_item : " << CMI_address_item->str_value << std::endl;

					/* MODE = RP */
					// AltiLab::DataObject * MODE_dataobject = doc->find_dataobject("MODE");
					// AltiLab::DataObjectItem * MODE_address_item = MODE_dataobject->find_dataobjectitem("address");
					// AltiLab::DataObjectItem * MODE_choicetype_item = MODE_dataobject->find_dataobjectitem("choicetype");
					// AltiLab::ChoiceType * MODE_choicetype = doc->find_choicetype(MODE_choicetype_item->str_value);
					// AltiLab::Choice * MODE_choice = MODE_choicetype->find_choice("RP");
					// std::cout << "MODE_address_item : " << MODE_address_item->str_value << std::endl;
					// std::cout << "MODE_choice : " << MODE_choice->str_value << std::endl;
				// }
			}
		}
		else if (bic_cfg->getCtrl()->str_iface == "serial")
		{
			BIC::CtrlConfigSerial * bic_serial = (BIC::CtrlConfigSerial *)bic_base;
			Modbus::ModbusChannel * modbus_serial = factory.rtu(bic_serial->str_device, std::strtol(bic_serial->str_baud.c_str(), 0, 0));
			AltiLab::DataObject * IM00_dataobject = altilab_doc->find_dataobject("IM00"); // IM00
			AltiLab::DataObjectItem * IM00_address_item = IM00_dataobject->find_dataobjectitem("address");
			std::cout << "IM00_address_item : " << IM00_address_item->str_value << std::endl;
			std::cout << "IM00_address_item : " << IM00_address_item->str_type << std::endl;

			if (IM00_address_item->str_type == "modbus")
			{
				AltiLab::DataObjectItem * IM00_choicetype_item = IM00_dataobject->find_dataobjectitem("choicetype");
				AltiLab::ChoiceType * IM00_choicetype = altilab_doc->find_choicetype(IM00_choicetype_item->str_value);
				AltiLab::Choice * IM00_choice = IM00_choicetype->find_choice("DHCP"); // DHCP
				std::cout << "IM00_choice : " << IM00_choice->str_value << std::endl;

				Modbus::ModbusMsgFC06 IM00_msg;
				IM00_msg.setSlaveAddress(std::strtoul(bic_modbus->str_slave_address.c_str(), 0, 0));
				IM00_msg.setRegister(std::strtoul(IM00_address_item->str_value.c_str(), 0, 0), std::strtoul(IM00_choice->str_value.c_str(), 0, 0));
				modbus_serial->sendFC(&IM00_msg);
			}
		}
	}
	catch(Modbus::ModbusException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(BIC::Exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(AltiLab::Exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "exception" << std::endl;
	}

	fin = 1;
	t1.join();
	t2.join();
	std::cout << "FIN" << std::endl;
	
	delete BIC::Factory::getInstance();

	return 0;
}