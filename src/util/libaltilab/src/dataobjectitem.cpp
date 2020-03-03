#include "libaltilab/dataobjectitem.h"
#include "libaltilab/exception.h"
// #include "log.h"
// #include <iostream>
// #include <iomanip>
// #include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <iostream>

AltiLab::DataObjectItem::DataObjectItem()
{}

AltiLab::DataObjectItem::~DataObjectItem()
{}

// uint16_t AltiLab::DataObjectItem::byteSize()
// {
	// uint16_t value = 0;
	// if (str_bytesize.size() > 0)
	// {
		// char * end;
		// value = std::strtoul(str_bytesize.c_str(), &end, 0);
	// }
	// return value;
// }

// uint64_t AltiLab::DataObjectItem::address()
// {
	// uint64_t value = 0;
	// if (str_address.size() > 0)
	// {
		// char * end;
		// value = std::strtoull(str_address.c_str(), &end, 0);
	// }
	// return value;
// }

// uint16_t AltiLab::DataObjectItem::modifiable()
// {
	// return (str_modifiable != "never");
// }

void AltiLab::DataObjectItem::xml_item(xmlNode * a_node)
{
	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (attr->children)
		{
			if (!xmlStrcmp(attr->name, (const xmlChar *)"type"))
			{
				str_type = std::string((const char *)attr->children->content);
			}
		}
		attr = attr->next;
	}

	str_name = std::string((const char *)a_node->name);
	str_value = std::string((const char *)a_node->children->content);

	// std::cout << "str_name : " << str_name << " str_value : " << str_value << " str_type : " << str_type << std::endl;
}
