#include "libbic/index.h"
#include "libbic/command.h"
#include "libbic/cmdmodbus.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>


BIC::Command * BIC::Index::find_cmd(const std::string & p_id)
{
	std::map < std::string, BIC::Command * >::iterator it = map_cmd.find(p_id);
	if (it != map_cmd.end())
	{
		return it->second;
	}
	
	throw BIC::Exception(__FILE__, __LINE__, "cmd plc non trouve");
}

void BIC::Index::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
		{
			str_id = std::string((const char *)attr->children->content);
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
				BIC::Command * cmd = new BIC::CommandModbus();
				cmd->xml_read(child_node);
				map_cmd[cmd->str_protocol] = cmd;
			}
		}

		child_node = child_node->next;	
	}
}
