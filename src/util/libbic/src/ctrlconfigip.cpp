#include "libbic/ctrlconfigip.h"
#include "libbic/element.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::CtrlConfigIp::CtrlConfigIp()
: BIC::CtrlConfigBase("ethernet")
, elem_mode(0)
, elem_address(0)
, elem_port(0)
, elem_mask(0)
, elem_gw(0)
{}

BIC::CtrlConfigIp::~CtrlConfigIp()
{
	delete elem_mode;
	delete elem_address;
	delete elem_port;
	delete elem_mask;
	delete elem_gw;
}

// int16_t BIC::CtrlConfigIp::getPort()
// {
	// int16_t value;
	// if (str_port.size() > 0)
	// {
		// char * end;
		// value = std::strtol(str_port.c_str(), &end, 0);
	// }
	// return value;
// }

void BIC::CtrlConfigIp::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	// xmlAttr *attr = a_node->properties;
	// while ( attr )
	// {
		// if (!xmlStrcmp(attr->name, (const xmlChar *)"iface"))
		// {
			// str_iface = std::string((const char *)attr->children->content);
		// }
		// attr = attr->next;
	// }

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"mode"))
			{
				elem_mode = new Element((char *)child_node->name);
				elem_mode->xml_read(child_node);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"address"))
			{
				elem_address = new Element((char *)child_node->name);
				elem_address->xml_read(child_node);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"port"))
			{
				elem_port = new Element((char *)child_node->name);
				elem_port->xml_read(child_node);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"mask"))
			{
				elem_mask = new Element((char *)child_node->name);
				elem_mask->xml_read(child_node);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"gateway"))
			{
				elem_gw = new Element((char *)child_node->name);
				elem_gw->xml_read(child_node);
			}
		}

		child_node = child_node->next;
	}
}
