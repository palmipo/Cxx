#include "libaltilab/group.h"
#include "libaltilab/groupitem.h"
#include "libaltilab/exception.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

AltiLab::Group::Group()
{}

AltiLab::Group::~Group()
{}

AltiLab::GroupItem * AltiLab::Group::find_groupitem(const std::string & choicetype)
{
	std::map < std::string, AltiLab::GroupItem * >::iterator it_choice = map_goupItem.find(choicetype);
	if (it_choice != map_goupItem.end())
	{
		return it_choice->second;
	}

	throw AltiLab::Exception(__FILE__, __LINE__, "GroupItem inconnu.");
}

void AltiLab::Group::xml_group(xmlNode * a_node)
{
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (attr->children && !xmlStrcmp(attr->name, (const xmlChar *)"name"))
		{
			str_name = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"item"))
			{
				AltiLab::GroupItem * item = new AltiLab::GroupItem();
				item->xml_item(child_node);
				map_goupItem[item->str_id] = item;
			}
		}

		child_node = child_node->next;
	}
}
