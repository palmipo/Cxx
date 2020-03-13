#include "libbic/ctrlconfigcanatnet.h"
#include "libbic/ctrlconfigip.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::CtrlConfigCanAtNet::CtrlConfigCanAtNet()
: BIC::CtrlConfigBase("canatnet")
{}

// BIC::CtrlConfigCanAtNet::~CtrlConfigCanAtNet()
// {}

// int16_t BIC::CtrlConfigCanAtNet::getPort()
// {
	// int16_t value;
	// if (str_port.size() > 0)
	// {
		// char * end;
		// value = std::strtol(str_port.c_str(), &end, 0);
	// }
	// return value;
// }

void BIC::CtrlConfigCanAtNet::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"ip"))
			{
				BIC::CtrlConfigIp * cfg = new BIC::CtrlConfigIp();
				cfg->xml_read(child_node);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"baud"))
			{
				str_baud = std::string((const char *)child_node->children->content);
			}
		}

		child_node = child_node->next;
	}
}
