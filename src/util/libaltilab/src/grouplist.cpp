#include "libaltilab/grouplist.h"
#include "libaltilab/group.h"
#include "libaltilab/exception.h"
// #include "log.h"
// #include <iostream>
// #include <iomanip>
// #include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

AltiLab::GroupList::GroupList()
{}

AltiLab::GroupList::~GroupList()
{}

AltiLab::Group * AltiLab::GroupList::find_group(const std::string & choicetype)
{
	std::map < std::string, AltiLab::Group * >::iterator it_choice = map_group.find(choicetype);
	if (it_choice != map_group.end())
	{
		return it_choice->second;
	}

	throw AltiLab::Exception(__FILE__, __LINE__, "Group inconnu.");
}

void AltiLab::GroupList::xml_grouplist(xmlNode * a_node)
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
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"group"))
			{
				AltiLab::Group * grp = new AltiLab::Group();
				grp->xml_group(child_node);
				map_group[grp->str_name] = grp;
			}
		}

		child_node = child_node->next;
	}
}
