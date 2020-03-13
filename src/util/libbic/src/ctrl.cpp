#include "libbic/ctrl.h"
#include "libbic/factory.h"
#include "libbic/ctrlconfig.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Ctrl::Ctrl()
: cfg(0)
{}

BIC::Ctrl::~Ctrl()
{
	delete cfg;
}

BIC::CtrlConfig * BIC::Ctrl::getCfg()
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	
	if (cfg)
	{
		return cfg;
	}

	throw BIC::Exception(__FILE__, __LINE__, "controleur inexistante");
}

void BIC::Ctrl::xml_read(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	xmlAttr *attr = a_node->properties;
	while ( attr )
	{
		if (!xmlStrcmp(attr->name, (const xmlChar *)"id"))
		{
			str_ctrl_id = std::string((const char *)attr->children->content);
		}
		else if (!xmlStrcmp(attr->name, (const xmlChar *)"type"))
		{
			str_type = std::string((const char *)attr->children->content);
		}
		attr = attr->next;
	}


	xmlNode *child_node = a_node->xmlChildrenNode;
	try
	{
		cfg = BIC::Factory::getInstance()->find_ctrl(str_ctrl_id)->getCfg();
		if (child_node)
		{
			cfg->xml_read(str_ctrl_id, child_node);
		}
	}
	catch(BIC::Exception)
	{
		while (child_node)
		{
			if (child_node->type == XML_ELEMENT_NODE)
			{
				if (!xmlStrcmp(child_node->name, (const xmlChar *)"config"))
				{
					cfg = new BIC::CtrlConfig();
					cfg->xml_read(str_ctrl_id, child_node);
				}
			}

			child_node = child_node->next;
		}
	}
}

// BIC::Ctrl& BIC::Ctrl::operator=(const BIC::Ctrl & b)
// {
	// str_ctrl_id = b.str_ctrl_id;
	// str_type = b.str_type;
	// *cfg = *(b.cfg);

	// return *this;
// }
