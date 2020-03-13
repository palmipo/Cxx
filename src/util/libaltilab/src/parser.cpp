#include "libaltilab/parser.h"
#include "libaltilab/dataobjectcollection.h"
#include "libaltilab/exception.h"
// #include "log.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
// #include <exception>

AltiLab::Parser::Parser(const std::string & fichier_xml)
{
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    xmlDoc *doc = xmlReadFile(fichier_xml.c_str(), NULL, 0);
    if (doc == NULL)
	{
        std::cerr << "error: could not parse file " << fichier_xml << std::endl;
    }
	else
	{
		/*Get the root element node */
		xmlNode *root_element = xmlDocGetRootElement(doc);

		xml_device(root_element);

		/*free the document */
		xmlFreeDoc(doc);
	}
}

AltiLab::Parser::~Parser()
{
    xmlCleanupParser();

	std::map < std::tuple < std::string, std::string, std::string >, AltiLab::DataObjectCollection * >::iterator it = map_data_object.begin();
	while (it != map_data_object.end())
	{
		delete it->second;
		++it;
	}
}

AltiLab::DataObjectCollection * AltiLab::Parser::dataObject(const std::string & defaultgroupname, const std::string & defaultgroupname_id, const std::string & defaultgroupname_name)
{
	std::map < std::tuple < std::string, std::string, std::string >, AltiLab::DataObjectCollection * >::iterator it = map_data_object.find(std::make_tuple(defaultgroupname, defaultgroupname_id, defaultgroupname_name));
	if (it != map_data_object.end())
	{
		return it->second;
	}

	throw AltiLab::Exception(__FILE__, __LINE__, "fichier xml incomplet !");
}

void AltiLab::Parser::xml_device(xmlNode * a_node)
{
	if (a_node->type == XML_ELEMENT_NODE)
	{
		if (!xmlStrcmp(a_node->name, (const xmlChar *)"device"))
		{
			xmlNode *cur_node = a_node->xmlChildrenNode;
			while (cur_node)
			{
				if (cur_node->type == XML_ELEMENT_NODE)
				{
					if (!xmlStrcmp(cur_node->name, (const xmlChar *)"dataobjectcollection"))
					{
						AltiLab::DataObjectCollection * obj = new AltiLab::DataObjectCollection();
						obj->xml_dataobjectcollection(cur_node);
						map_data_object[std::make_tuple(obj->str_defaultgroupname, obj->str_id, obj->str_name)] = obj;
					}
				}
				
				cur_node = cur_node->next;
			}
		}
    }
}
