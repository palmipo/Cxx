#include "libbic/factory.h"
#include "libbic/interface.h"
#include "libbic/plc.h"
#include "libbic/drive.h"
#include "libbic/ctrl.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Factory * _instance = 0;

BIC::Factory::Factory()
{}

BIC::Factory::~Factory()
{
	std::map < std::string, BIC::Drive * >::iterator it1 = map_drive.begin();
	while (it1 != map_drive.end())
	{
		delete it1->second;
		++it1;
	}
	std::map < std::string, BIC::Plc * >::iterator it2 = map_plc.begin();
	while (it2 != map_plc.end())
	{
		delete it2->second;
		++it2;
	}
	std::map < std::string, BIC::Ctrl * >::iterator it3 = map_ctrl.begin();
	while (it3 != map_ctrl.end())
	{
		delete it3->second;
		++it3;
	}
}

BIC::Factory * BIC::Factory::getInstance()
{
	if (!_instance)
	{
		_instance = new BIC::Factory();
	}

	return _instance;
}

void BIC::Factory::readConfigFile(const std::string & fic)
{
	BIC::Interface itf(fic);
}

void BIC::Factory::add_ctrl(BIC::Ctrl * ctrl)
{
	try
	{
		BIC::Ctrl * tmp = find_ctrl(ctrl->str_ctrl_id);
		*tmp = *ctrl;
	}
	catch(BIC::Exception)
	{
		map_ctrl[ctrl->str_ctrl_id] = ctrl;
		BIC::Exception(__FILE__, __LINE__, "add_ctrl : " + ctrl->str_ctrl_id);
	}
}

BIC::Ctrl * BIC::Factory::find_ctrl(std::string ctrl_id)
{
	std::map < std::string , BIC::Ctrl * >::iterator it_ctrl = map_ctrl.find(ctrl_id);
	if (it_ctrl != map_ctrl.end())
	{
		return it_ctrl->second;
	}

	throw BIC::Exception(__FILE__, __LINE__, "ctrl : " + ctrl_id + " inconnu du fichier de configuration !");
}

void BIC::Factory::xml_ctrl(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"controleur"))
			{
				BIC::Ctrl * ctrl = new BIC::Ctrl();
				ctrl->xml_read(child_node);
				add_ctrl(ctrl);
			}
		}

		child_node = child_node->next;
	}
}

BIC::Drive * BIC::Factory::find_drive (std::string drive_id)
{
	BIC::Drive * drive = 0;

	std::map < std::string, BIC::Drive * >::iterator it_drive = map_drive.find(drive_id);
	if (it_drive != map_drive.end())
	{
		return it_drive->second;
	}
	
	throw BIC::Exception(__FILE__, __LINE__, "drive : " + drive_id + " inconnu du fichier de configuration !");
}

void BIC::Factory::xml_drives(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlNode *child_node = a_node->xmlChildrenNode;
	while (child_node)
	{
		if (child_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(child_node->name, (const xmlChar *)"drive"))
			{
				BIC::Drive * drive = new BIC::Drive();
				drive->xml_read(child_node);
				map_drive[drive->str_drive_id] = drive;
			}
		}

		child_node = child_node->next;
	}
}

BIC::Plc * BIC::Factory::find_plc (std::string plc_id)
{
	std::map < std::string, BIC::Plc * >::iterator it_plc = map_plc.find(plc_id);
	if (it_plc != map_plc.end())
	{
		return it_plc->second;
	}

	throw BIC::Exception(__FILE__, __LINE__, "plc : " + plc_id + " inconnu du fichier de configuration !");
}

void BIC::Factory::xml_plc(xmlNode * a_node)
{
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
	xmlNode * ctrl_node = a_node->xmlChildrenNode;
	while (ctrl_node)
	{
		if (ctrl_node->type == XML_ELEMENT_NODE)
		{
			if (!xmlStrcmp(ctrl_node->name, (const xmlChar *)"plc"))
			{
				BIC::Plc * plc = new BIC::Plc();
				plc->xml_read(ctrl_node);
				map_plc[plc->str_plc_id] = plc;
			}
		}

		ctrl_node = ctrl_node->next;
	}
}
