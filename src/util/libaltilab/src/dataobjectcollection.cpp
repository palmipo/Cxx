#include "libaltilab/dataobjectcollection.h"
#include "libaltilab/dataobjectlist.h"
#include "libaltilab/dataobject.h"
#include "libaltilab/grouplist.h"
#include "libaltilab/choicetypelist.h"
#include "libaltilab/choicetype.h"
#include "libaltilab/exception.h"
// #include "log.h"
// #include <iostream>
// #include <iomanip>
// #include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

AltiLab::DataObjectCollection::DataObjectCollection()
{}

AltiLab::DataObjectCollection::~DataObjectCollection()
{
	// std::map < std::string, AltiLab::Register * >::iterator it1 = map_registers.begin();
	// while (it1 != map_registers.end())
	// {
		// delete it1->second;
		// ++it1;
	// }

	// std::map < std::string, RegistreChoiceType * >::iterator it2 = map_choice_type.begin();
	// while (it2 != map_choice_type.end())
	// {
		// delete it2->second;
		// ++it2;
	// }
}

uint32_t AltiLab::DataObjectCollection::cpu()
{
	uint32_t value = 0;
	if (str_cpu.size() > 0)
	{
		value = std::strtoul(str_cpu.c_str(), 0, 0);
	}
	return value;
}

AltiLab::DataObject * AltiLab::DataObjectCollection::find_dataobject(const std::string & registre_id)
{
	std::list < AltiLab::DataObjectList * >::iterator it = list_dataobjectlist.begin();
	while (it != list_dataobjectlist.end())
	{
		try
		{
			return (*it)->find_dataobject(registre_id);
		}
		catch(...)
		{}
	}
	
	throw AltiLab::Exception(__FILE__, __LINE__, "register inconnu !");
}

AltiLab::ChoiceType * AltiLab::DataObjectCollection::find_choicetype(const std::string & registre_id)
{
	std::list < AltiLab::ChoiceTypeList * >::iterator it = list_choicetypelist.begin();
	while (it != list_choicetypelist.end())
	{
		try
		{
			return (*it)->find_choicetype(registre_id);
		}
		catch(...)
		{}
	}
	
	throw AltiLab::Exception(__FILE__, __LINE__, "register inconnu !");
}

AltiLab::GroupList * AltiLab::DataObjectCollection::find_grouplist(const std::string & choicetype)
{
	std::map < std::string, AltiLab::GroupList * >::iterator it_choice = map_grouplist.find(choicetype);
	if (it_choice != map_grouplist.end())
	{
		return it_choice->second;
	}

	throw AltiLab::Exception(__FILE__, __LINE__, "GroupList inconnu.");
}

void AltiLab::DataObjectCollection::xml_dataobjectcollection(xmlNode * a_node)
{
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (attr->children)
		{
			if (!xmlStrcmp(attr->name, (const xmlChar *)"cpu"))
			{
				str_cpu = std::string((const char *)attr->children->content);
			}
			else if (!xmlStrcmp(attr->name, (const xmlChar *)"defaultgroupname"))
			{
				str_defaultgroupname = std::string((const char *)attr->children->content);
			}
			else if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
			{
				str_id = std::string((const char *)attr->children->content);
			}
			else if (!xmlStrcmp(attr->name, (const xmlChar *)"name"))
			{
				str_name = std::string((const char *)attr->children->content);
			}
		}
		attr = attr->next;
	}

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"dataobjectlist"))
			{
				AltiLab::DataObjectList * item = new AltiLab::DataObjectList();
				item->xml_dataobjectlist(child_node);
				list_dataobjectlist.push_back(item);
			}
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"choicetypelist"))
			{
				AltiLab::ChoiceTypeList * item = new AltiLab::ChoiceTypeList();
				item->xml_choicetypelist(child_node);
				list_choicetypelist.push_back(item);
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"grouplist"))
			{
				AltiLab::GroupList * item = new AltiLab::GroupList();
				item->xml_grouplist(child_node);
				map_grouplist[item->str_name] = item;
			}
		}

		child_node = child_node->next;
	}
}
