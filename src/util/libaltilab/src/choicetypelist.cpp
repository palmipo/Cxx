#include "libaltilab/choicetypelist.h"
#include "libaltilab/choicetype.h"
#include "libaltilab/exception.h"
// #include "log.h"
// #include <iostream>
// #include <iomanip>
// #include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>

AltiLab::ChoiceTypeList::ChoiceTypeList()
{}

AltiLab::ChoiceTypeList::~ChoiceTypeList()
{}

AltiLab::ChoiceType * AltiLab::ChoiceTypeList::find_choicetype(const std::string & registre_id)
{
	std::map < std::string, AltiLab::ChoiceType * >::iterator it_reg = map_choices.find(registre_id);
	if (it_reg != map_choices.end())
	{
		return it_reg->second;
	}
	
	throw AltiLab::Exception(__FILE__, __LINE__, "register inconnu !");
}

void AltiLab::ChoiceTypeList::xml_choicetypelist(xmlNode * a_node)
{
	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"choicetype"))
			{
				AltiLab::ChoiceType * choiceType = new AltiLab::ChoiceType();
				choiceType->xml_choicetype(child_node);
				map_choices[choiceType->str_id] = choiceType;
			}
		}

		child_node = child_node->next;
	}
}

