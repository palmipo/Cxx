#include "libbic/canbus.h"
#include "libbic/factory.h"
#include "libbic/ctrl.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

// uint8_t BIC::Canbus::getNodeId()
// {
	// uint8_t value = 0;
	// if (str_node_id.size() > 0)
	// {
		// char * end;
		// value = std::strtoul(str_node_id.c_str(), &end, 0);
	// }
	// return value;
// }

void BIC::Canbus::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"iface"))
		{
			str_iface = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"node_id"))
			{
				str_node_id = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"controleur"))
			{
				BIC::Ctrl * ctrl = new BIC::Ctrl();
				ctrl->xml_read(child_node);
				BIC::Factory::getInstance()->add_ctrl(ctrl);
				str_ctrl_id = ctrl->str_ctrl_id;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"fichier"))
			{
				str_config_xml = std::string((const char *)child_node->children->content);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"protocole"))
			{
				str_protocole = std::string((const char *)child_node->children->content);
			}
		}

		child_node = child_node->next;
	}
}
