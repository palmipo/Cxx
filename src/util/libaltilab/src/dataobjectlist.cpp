#include "libaltilab/dataobjectlist.h"
#include "libaltilab/dataobject.h"
#include "libaltilab/exception.h"
// #include "log.h"
// #include <iostream>
// #include <iomanip>
// #include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

AltiLab::DataObjectList::DataObjectList()
{}

AltiLab::DataObjectList::~DataObjectList()
{}


AltiLab::DataObject * AltiLab::DataObjectList::find_dataobject(const std::string & registre_id)
{
	std::map < std::string, AltiLab::DataObject * >::iterator it_reg = map_dataobject.find(registre_id);
	if (it_reg != map_dataobject.end())
	{
		return it_reg->second;
	}
	
	throw AltiLab::Exception(__FILE__, __LINE__, "register inconnu !");
}

void AltiLab::DataObjectList::xml_dataobjectlist(xmlNode * a_node)
{
	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"dataobject"))
			{
				AltiLab::DataObject * n_reg = new AltiLab::DataObject();
				n_reg->xml_dataobject(child_node);
				map_dataobject[n_reg->str_id] = n_reg;
			}
		}

		child_node = child_node->next;
	}
}
