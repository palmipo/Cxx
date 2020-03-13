#include "libbic/cmdmodbus.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::CommandModbus::CommandModbus()
: Command("modbus")
{}

BIC::CommandModbus::~CommandModbus()
{}

uint8_t BIC::CommandModbus::getReadfct()
{
	uint8_t value;
	if (str_read_fct.size() > 0)
	{
		value = std::strtoul(str_read_fct.c_str(), 0, 0);
	}
	return value;
}

uint8_t BIC::CommandModbus::getWritefct()
{
	uint8_t value;
	if (str_write_fct.size() > 0)
	{
		value = std::strtoul(str_write_fct.c_str(), 0, 0);
	}
	return value;
}

uint16_t BIC::CommandModbus::getRegisterValue()
{
	uint16_t value = 0;
	if (str_registre.size() > 0)
	{
		value = std::strtoul(str_registre.c_str(), 0, 0);
	}
	return value;
}

uint16_t BIC::CommandModbus::getRegisterNumber()
{
	uint16_t value = 0;
	if (str_nb_registre.size() > 0)
	{
		value = std::strtoul(str_nb_registre.c_str(), 0, 0);
	}
	return value;
}

uint16_t BIC::CommandModbus::getMask()
{
	uint16_t value = 0;
	if (str_mask.size() > 0)
	{
		value = std::strtoul(str_mask.c_str(), 0, 0);
	}
	return value;
}

uint16_t BIC::CommandModbus::getHighValue()
{
	uint16_t value = 0;
	if (str_hight_value.size() > 0)
	{
		value = std::strtoul(str_hight_value.c_str(), 0, 0);
	}
	return value;
}

uint16_t BIC::CommandModbus::getLowValue()
{
	uint16_t value = 0;
	if (str_low_value.size() > 0)
	{
		value = std::strtoul(str_low_value.c_str(), 0, 0);
	}
	return value;
}
uint16_t BIC::CommandModbus::getVoltageValue()
{
	uint16_t value = 0;
	if (str_voltage_value.size() > 0)
	{
		value = std::strtoul(str_voltage_value.c_str(), 0, 0);
	}
	return value;
}

uint16_t BIC::CommandModbus::getCurrentValue()
{
	uint16_t value = 0;
	if (str_current_value.size() > 0)
	{
		value = std::strtoul(str_current_value.c_str(), 0, 0);
	}
	return value;
}


void BIC::CommandModbus::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	// xmlAttr *attr = a_node->properties;
	// while ( attr )
	// {
		// if (!xmlStrcmp(attr->name, (const xmlChar *)"protocol"))
		// {
			// str_protocol = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"readFC"))
		// {
			// str_read_fct = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"writeFC"))
		// {
			// str_write_fct = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"registre"))
		// {
			// str_registre = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"nb_registre"))
		// {
			// str_nb_registre = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"mask"))
		// {
			// str_mask = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"hight_value"))
		// {
			// str_hight_value = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"low_value"))
		// {
			// str_low_value = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"default_value"))
		// {
			// str_default_value = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"voltage_value"))
		// {
			// str_voltage_value = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"current_value"))
		// {
			// str_current_value = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"voltage_unit"))
		// {
			// str_voltage_unit = std::string((const char *)attr->children->content);
		// }
		// else if (!xmlStrcmp(attr->name, (const xmlChar *)"current_unit"))
		// {
			// str_current_unit = std::string((const char *)attr->children->content);
		// }
		// attr = attr->next;
	// }

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"readFC"))
			{
				str_read_fct = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"writeFC"))
			{
				str_write_fct = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"registre"))
			{
				str_registre = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"nb_registre"))
			{
				str_nb_registre = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"mask"))
			{
				str_mask = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"hight_value"))
			{
				str_hight_value = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"low_value"))
			{
				str_low_value = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"default_value"))
			{
				str_default_value = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"voltage_value"))
			{
				str_voltage_value = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"current_value"))
			{
				str_current_value = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"voltage_unit"))
			{
				str_voltage_unit = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"current_unit"))
			{
				str_current_unit = std::string((const char *)child_node->children->content);
			}
		}

		child_node = child_node->next;	
	}
}
