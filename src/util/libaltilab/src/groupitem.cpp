#include "libaltilab/groupitem.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <iostream>

AltiLab::GroupItem::GroupItem()
{}

AltiLab::GroupItem::~GroupItem()
{}

void AltiLab::GroupItem::xml_item(xmlNode * a_node)
{
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (attr->children && !xmlStrcmp(attr->name, (const xmlChar *)"id"))
		{
			str_id = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}

	// std::cout << "str_id : " << str_id << std::endl;
}