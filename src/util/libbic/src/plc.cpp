#include "libbic/plc.h"
#include "libbic/modbus.h"
#include "libbic/canbus.h"
#include "libbic/signal.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Plc::Plc()
{}

BIC::Plc::~Plc()
{
	std::map < std::string, BIC::Modbus * >::iterator it1 = map_modbus.begin();
	while (it1 != map_modbus.end())
	{
		delete it1->second;
		++it1;
	}

	std::map < std::string, BIC::Canbus * >::iterator it2 = map_canbus.begin();
	while (it2 != map_canbus.end())
	{
		delete it2->second;
		++it2;
	}

	std::map < std::string, BIC::Signal * >::iterator it3 = map_signaux.begin();
	while (it3 != map_signaux.end())
	{
		delete it3->second;
		++it3;
	}
}

BIC::Modbus * BIC::Plc::getModbus(const std::string & iface)
{
	std::map < std::string, BIC::Modbus * >::iterator it = map_modbus.find(iface);
	if (it != map_modbus.end())
	{
		return it->second;
	}	

	std::stringstream ss;
	ss << "pas de config modbus : " << iface;
	throw BIC::Exception(__FILE__, __LINE__, ss.str());
}

BIC::Canbus * BIC::Plc::getCanbus(const std::string & iface)
{
	std::map < std::string, BIC::Canbus * >::iterator it = map_canbus.find(iface);
	if (it != map_canbus.end())
	{
		return it->second;
	}	
	
	throw BIC::Exception(__FILE__, __LINE__, "pas de config canopen");
}

BIC::Signal * BIC::Plc::find_signal(const std::string & p_id)
{
	std::map < std::string, BIC::Signal * >::iterator it = map_signaux.find(p_id);
	if (it != map_signaux.end())
	{
		return it->second;
	}
	
	throw BIC::Exception(__FILE__, __LINE__, "signal plc non trouve");
}

void BIC::Plc::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	// lecture des attributs
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
		{
			str_plc_id = std::string((const char *)attr->children->content);
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
				map_modbus[bus->str_iface] = bus;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"canopen"))
			{
				BIC::Canbus * bus = new BIC::Canbus();
				bus->xml_read(child_node);
				map_canbus[bus->str_iface] = bus;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"signal"))
			{
				BIC::Signal * bus = new BIC::Signal();
				bus->xml_read(child_node);
				map_signaux[bus->str_signal_id] = bus;
			}
		}

		child_node = child_node->next;
	}
}
