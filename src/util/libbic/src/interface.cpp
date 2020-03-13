#include "libbic/interface.h"
#include "libbic/factory.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Interface::Interface(const std::string & fichier_xml)
{
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    xmlDoc *doc = xmlReadFile(fichier_xml.c_str(), NULL, 0);
    if (doc == NULL)
	{
		std::stringstream ss;
		ss << "error: could not parse file " << fichier_xml;
		throw BIC::Exception(__FILE__, __LINE__, ss.str());
    }
	else
	{
		/*Get the root element node */
		xmlNode *root_element = xmlDocGetRootElement(doc);

		xml_read(root_element);

		/*free the document */
		xmlFreeDoc(doc);
	}
}

BIC::Interface::~Interface()
{
    xmlCleanupParser();
}

void BIC::Interface::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	if (a_node->type == XML_ELEMENT_NODE)
	{
		if (!xmlStrcmp(a_node->name, (const xmlChar *)"interface"))
		{
			xmlNode * cur_node = a_node->xmlChildrenNode;
			while (cur_node)
			{
				if (cur_node->type == XML_ELEMENT_NODE)
				{
					if (!xmlStrcmp(cur_node->name, (const xmlChar *)"controleurs"))
					{
						BIC::Factory::getInstance()->xml_ctrl(cur_node);
					}
					else if (!xmlStrcmp(cur_node->name, (const xmlChar *)"drives"))
					{
						BIC::Factory::getInstance()->xml_drives(cur_node);
					}
					else if (!xmlStrcmp(cur_node->name, (const xmlChar *)"automates"))
					{
						BIC::Factory::getInstance()->xml_plc(cur_node);
					}
				}

				cur_node = cur_node->next;
			}
		}
    }
}
