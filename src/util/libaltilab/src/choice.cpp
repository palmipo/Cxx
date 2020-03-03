#include "libaltilab/choice.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <iostream>

AltiLab::Choice::Choice()
{}

AltiLab::Choice::~Choice()
{}

void AltiLab::Choice::xml_choice(xmlNode * a_node)
{
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (attr->children)
		{
			if (!xmlStrcmp(attr->name, (const xmlChar *)"description"))
			{
				str_description = std::string((const char *)attr->children->content);
			}
			else if (!xmlStrcmp(attr->name, (const xmlChar *)"value"))
			{
				str_value = std::string((const char *)attr->children->content);
			}
		}
		attr = attr->next;
	}

	str_choice = std::string((const char *)a_node->children->content);
	
	// std::cout << "str_choice : " << str_choice << " str_description : " << str_description << " str_value : " << str_value << std::endl;
}
