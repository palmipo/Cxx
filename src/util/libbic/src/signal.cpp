#include "libbic/signal.h"
#include "libbic/index.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>


BIC::Index * BIC::Signal::find_index(const std::string & id)
{
	std::map < std::string, BIC::Index * >::iterator it = map_signaux.find(id);
	if (it != map_signaux.end())
	{
		return it->second;
	}
	
	throw BIC::Exception(__FILE__, __LINE__, "index plc non trouve");
}

void BIC::Signal::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
		{
			str_signal_id = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"index"))
			{
				BIC::Index * signal = new BIC::Index();
				signal->xml_read(child_node);
				map_signaux[signal->str_id] = signal;
			}
		}

		child_node = child_node->next;
	}
}
