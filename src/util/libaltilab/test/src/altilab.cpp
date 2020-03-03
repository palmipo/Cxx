#include "libaltilab/altilab.h"
#include "modbus/tcp/Master.hpp"
#include "os/Timeout.hpp"
#include <iostream>

int main(int argc, char ** argv)
{
	try
	{
		modbus::tcp::Master node;
		// node.connect("192.168.1.101");

		AltiLab::Parser parser(argv[1]);
		AltiLab::DataObjectCollection * doc = parser.dataObject();
		
		// IM00 = DHCP
		AltiLab::DataObject * IM00_dataobject = doc->find_dataobject("IM00");
		AltiLab::DataObjectItem * IM00_address_item = IM00_dataobject->find_dataobjectitem("address");
		std::cout << "IM00_address_item : " << IM00_address_item->str_value << std::endl;
		std::cout << "IM00_address_item : " << IM00_address_item->str_type << std::endl;
		
		if (IM00_address_item->str_type == "modbus")
		{
			AltiLab::DataObjectItem * IM00_choicetype_item = IM00_dataobject->find_dataobjectitem("choicetype");
			AltiLab::ChoiceType * IM00_choicetype = doc->find_choicetype(IM00_choicetype_item->str_value);
			AltiLab::Choice * IM00_choice = IM00_choicetype->find_choice("DHCP");
			std::cout << "IM00_choice : " << IM00_choice->str_value << std::endl;

			node.write_single_register(0xF8, std::strtoul(IM00_address_item->str_value.c_str(), 0, 0), std::strtoul(IM00_choice->str_value.c_str(), 0, 0));
			
			AltiLab::DataObjectItem * IM00_modifiable_item = IM00_dataobject->find_dataobjectitem("modifiable");
			std::cout << "IM00_modifiable_item : " << IM00_modifiable_item->str_value << std::endl;
			if (IM00_modifiable_item->str_value == "gatingOff")
			{
				// CMI = 2
				AltiLab::DataObject * CMI_dataobject = doc->find_dataobject("CMI");
				AltiLab::DataObjectItem * CMI_address_item = CMI_dataobject->find_dataobjectitem("address");
				std::cout << "CMI_address_item : " << CMI_address_item->str_value << std::endl;

				// MODE = RP
				AltiLab::DataObject * MODE_dataobject = doc->find_dataobject("MODE");
				AltiLab::DataObjectItem * MODE_address_item = MODE_dataobject->find_dataobjectitem("address");
				AltiLab::DataObjectItem * MODE_choicetype_item = MODE_dataobject->find_dataobjectitem("choicetype");
				AltiLab::ChoiceType * MODE_choicetype = doc->find_choicetype(MODE_choicetype_item->str_value);
				AltiLab::Choice * MODE_choice = MODE_choicetype->find_choice("RP");
				std::cout << "MODE_address_item : " << MODE_address_item->str_value << std::endl;
				std::cout << "MODE_choice : " << MODE_choice->str_value << std::endl;
			}
		}

		std::cout << "FIN" << std::endl;
	}
	catch(AltiLab::Exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}