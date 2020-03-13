#include "libbic/ctrlconfig.h"
#include "libbic/ctrlconfigbase.h"
#include "libbic/ctrlconfigip.h"
#include "libbic/ctrlconfigserial.h"
#include "libbic/ctrlconfigcanatnet.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::CtrlConfig::CtrlConfig()
: ctrl(0)
{}

BIC::CtrlConfig::~CtrlConfig()
{
	delete ctrl;
	// std::map < std::string, CtrlConfigBase * > ::iterator it = map_config.begin();
	// while (it != map_config.end())
	// {
		// delete it->second;
		// it++;
	// }
}

// BIC::CtrlConfigBase * BIC::CtrlConfig::find_config(std::string id)
// {
	// std::map < std::string , BIC::CtrlConfigBase * >::iterator it_ctrl = map_config.find(id);
	// if (it_ctrl != map_config.end())
	// {
		// return it_ctrl->second;
	// }

	// throw BIC::Exception(__FILE__, __LINE__, id + " inconnu du fichier de configuration !");
// }

BIC::CtrlConfigBase * BIC::CtrlConfig::getCtrl()
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	if (ctrl)
	{
		return ctrl;
	}

	throw BIC::Exception(__FILE__, __LINE__, "pas de config");
}

void BIC::CtrlConfig::xml_read(const std::string & id, xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"ip"))
			{
				// BIC::CtrlConfigBase * ctrl = new BIC::CtrlConfigIp();
				ctrl = new BIC::CtrlConfigIp();
				ctrl->xml_read(child_node);
				// map_config[ctrl->str_iface] = ctrl;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"serial"))
			{
				// BIC::CtrlConfigBase * ctrl = new BIC::CtrlConfigSerial();
				ctrl = new BIC::CtrlConfigSerial();
				ctrl->xml_read(child_node);
				std::cout << "********************************* SERIAL **********************************************" << std::endl;
				// map_config[ctrl->str_iface] = ctrl;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"canatnet"))
			{
				// BIC::CtrlConfigBase * ctrl = new BIC::CtrlConfigCanAtNet();
				ctrl = new BIC::CtrlConfigCanAtNet();
				ctrl->xml_read(child_node);
				// map_config[ctrl->str_iface] = ctrl;
			}
			else if (!xmlStrcmp(child_node->name, (const xmlChar *)"usbcan"))
			{
				// xml_read(child_node);
			}
		}

		child_node = child_node->next;
	}
	
}
