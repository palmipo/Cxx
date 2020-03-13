#include "libbic/ctrlconfigserial.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::CtrlConfigSerial::CtrlConfigSerial()
: BIC::CtrlConfigBase("serial")
{}

// int32_t BIC::CtrlConfigSerial::getParity()
// {
	// int32_t value;
	// if (str_parity.size() > 0)
	// {
		// char * end;
		// value = std::strtol(str_parity.c_str(), &end, 0);
	// }
	// return value;
// }

// int32_t BIC::CtrlConfigSerial::getStop()
// {
	// int32_t value;
	// if (str_stop.size() > 0)
	// {
		// char * end;
		// value = std::strtol(str_stop.c_str(), &end, 0);
	// }
	// return value;
// }

// int32_t BIC::CtrlConfigSerial::getBaud()
// {
	// int32_t value;
	// if (str_baud.size() > 0)
	// {
		// char * end;
		// value = std::strtol(str_baud.c_str(), &end, 0);
	// }
	// return value;
// }

// int16_t BIC::CtrlConfigSerial::getPort()
// {
	// int16_t value;
	// if (str_port.size() > 0)
	// {
		// char * end;
		// value = std::strtol(str_port.c_str(), &end, 0);
	// }
	// return value;
// }

void BIC::CtrlConfigSerial::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"device"))
			{
				str_device = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"baud"))
			{
				str_baud = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"data"))
			{
				str_data = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"parity"))
			{
				str_parity = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"stop"))
			{
				str_stop = std::string((const char *)child_node->children->content);
			}
		}

		child_node = child_node->next;
	}
}
