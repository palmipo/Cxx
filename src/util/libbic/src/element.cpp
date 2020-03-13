#include "libbic/element.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Element::Element(const std::string & balise)
{
	str_tag = balise;
}

BIC::Element::~Element()
{}

void BIC::Element::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	xmlAttr * attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"registre"))
		{
			str_register = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"nb_registre"))
		{
			str_nb_register = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}

	xmlNode * child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_TEXT_NODE)
		{
			str_value = std::string((const char *)child_node->content);
		}

		child_node = child_node->next;
	}
}
