#include "libbic/power.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Power::Power()
{}

BIC::Power::~Power()
{}

void BIC::Power::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"plc_id"))
		{
			str_plc_id = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"modbus_iface"))
		{
			str_modbus_iface = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"signal_id"))
		{
			str_signal_id = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"index_id"))
		{
			str_index_id = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}
}
