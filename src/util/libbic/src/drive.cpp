#include "libbic/drive.h"
#include "libbic/modbus.h"
#include "libbic/canbus.h"
#include "libbic/power.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Drive::Drive()
: power(0)
{}

BIC::Drive::~Drive()
{
	delete power;
	std::map < std::string, BIC::Modbus * >::iterator it1 = xml_modbus.begin();
	while (it1 != xml_modbus.end())
	{
		delete it1->second;
		++it1;
	}
	std::map < std::string, BIC::Canbus * >::iterator it2 = xml_canbus.begin();
	while (it2 != xml_canbus.end())
	{
		delete it2->second;
		++it2;
	}
	// std::map < std::tuple < std::string, std::string >, BIC::Signal * >::iterator it3 = map_signaux.begin();
	// while (it3 != map_signaux.end())
	// {
		// delete it3->second;
		// ++it3;
	// }
}

BIC::Power * BIC::Drive::getPower()
{
	if (power)
	{
		return power;
	}	

	throw BIC::Exception(__FILE__, __LINE__, "pas de config power");
}

BIC::Modbus * BIC::Drive::getModbus(const std::string & iface)
{
	std::map < std::string, BIC::Modbus * >::iterator it = xml_modbus.find(iface);
	if (it != xml_modbus.end())
	{
		return it->second;
	}	

	throw BIC::Exception(__FILE__, __LINE__, "pas de config modbus");
}

BIC::Canbus * BIC::Drive::getCanbus(const std::string & iface)
{
	std::map < std::string, BIC::Canbus * >::iterator it = xml_canbus.find(iface);
	if (it != xml_canbus.end())
	{
		return it->second;
	}	
	
	throw BIC::Exception(__FILE__, __LINE__, "pas de config canopen");
}

// BIC::Signal * BIC::Drive::find_signal (std::string signal_id, std::string id)
// {
	// std::map < std::tuple < std::string, std::string >, XmlSignal * >::iterator it_signal = map_signaux.find(std::make_tuple(signal_id, id));
	// if (it_signal != map_signaux.end())
	// {
		// return it_signal->second;
	// }

	// throw XmlException(__FILE__, __LINE__, "signal : " + signal_id + " inconnu du fichier de configuration !");
// }

void BIC::Drive::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
		{
			str_drive_id = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"type"))
		{
			str_type = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"devFeat"))
		{
			str_device_feature = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"devSys"))
		{
			str_system_feature = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"modbus"))
			{
				BIC::Modbus * bus = new BIC::Modbus();
				bus->xml_read(child_node);
				xml_modbus[bus->str_iface] = bus;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"canopen"))
			{
				BIC::Canbus * bus = new BIC::Canbus();
				bus->xml_read(child_node);
				xml_canbus[bus->str_iface] = bus;
			}
			// else if (!xmlStrcmp(child_node->name, (const xmlChar *)"signaux"))
			// {
				// print_element_drives_drive_signaux(drive, child_node);
			// }
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"power"))
			{
				power = new BIC::Power();
				power->xml_read(child_node);
			}
		}

		child_node = child_node->next;
	}
}
