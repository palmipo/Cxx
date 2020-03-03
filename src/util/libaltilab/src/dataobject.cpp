#include "libaltilab/dataobject.h"
#include "libaltilab/dataobjectitem.h"
#include "libaltilab/exception.h"
// #include "log.h"
// #include <iostream>
// #include <iomanip>
// #include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

AltiLab::DataObject::DataObject()
{}

AltiLab::DataObject::~DataObject()
{}

// uint16_t AltiLab::DataObject::byteSize()
// {
	// uint16_t value = 0;
	// if (str_bytesize.size() > 0)
	// {
		// char * end;
		// value = std::strtoul(str_bytesize.c_str(), &end, 0);
	// }
	// return value;
// }

// uint64_t AltiLab::DataObject::address()
// {
	// uint64_t value = 0;
	// if (str_address.size() > 0)
	// {
		// char * end;
		// value = std::strtoull(str_address.c_str(), &end, 0);
	// }
	// return value;
// }

// uint16_t AltiLab::DataObject::modifiable()
// {
	// return (str_modifiable != "never");
// }


AltiLab::DataObjectItem * AltiLab::DataObject::find_dataobjectitem(const std::string & item)
{
	std::map < std::string, AltiLab::DataObjectItem * >::iterator it_reg = map_item.find(item);
	if (it_reg != map_item.end())
	{
		return it_reg->second;
	}
	
	throw AltiLab::Exception(__FILE__, __LINE__, "register inconnu !");
}

void AltiLab::DataObject::xml_dataobject(xmlNode * a_node)
{
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (attr->children)
		{
			if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
			{
				str_id = std::string((const char *)attr->children->content);
			}
		}
		attr = attr->next;
	}

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if ((child_node->type == XML_ELEMENT_NODE) && (child_node->children))
		{
			AltiLab::DataObjectItem * item = new AltiLab::DataObjectItem();
			item->xml_item(child_node);
			map_item[item->str_name] = item;
		}

		child_node = child_node->next;
	}
}
