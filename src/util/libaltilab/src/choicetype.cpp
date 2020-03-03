#include "libaltilab/choicetype.h"
#include "libaltilab/choice.h"
#include "libaltilab/exception.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

AltiLab::ChoiceType::ChoiceType()
{}

AltiLab::ChoiceType::~ChoiceType()
{}

AltiLab::Choice * AltiLab::ChoiceType::find_value(const std::string & value)
{
	std::map < std::string, AltiLab::Choice * >::iterator it_value = map_choices.find(value);
	if (it_value != map_choices.end())
	{
		return it_value->second;
	}

	throw AltiLab::Exception(__FILE__, __LINE__, "value inconnu !");
}

AltiLab::Choice * AltiLab::ChoiceType::find_choice(const std::string & str_choice)
{
	std::map < std::string, AltiLab::Choice * >::iterator it_value = map_choices.begin();
	while (it_value != map_choices.end())
	{
		if (it_value->second->str_choice == str_choice)
		{
			return it_value->second;
		}
		
		it_value++;
	}

	throw AltiLab::Exception(__FILE__, __LINE__, "choice inconnu !");
}

void AltiLab::ChoiceType::xml_choicetype(xmlNode * a_node)
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

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"choice"))
			{
				AltiLab::Choice * chx = new AltiLab::Choice();
				chx->xml_choice(child_node);
				map_choices[chx->str_value] = chx;
			}
		}

		child_node = child_node->next;
	}
}
