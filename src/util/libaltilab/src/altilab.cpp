#include "libaltilab/altilab.h"

AltiLab::Rapide(const std::string & fichier)
{
	AltiLab::Parser parser(fichier);
	AltiLab::DataObjectCollection * doc = parser.dataObject();
}

AltiLab::Rapide::registre(const std::string & reg)
{
	AltiLab::DataObject * IM00_dataobject = doc->find_dataobject(reg);

	AltiLab::DataObjectItem * shortname_item = dataobject->find_dataobjectitem("shortname");
	str_shortname = shortname_item->str_value;

	AltiLab::DataObjectItem * longname_item = dataobject->find_dataobjectitem("longname");
	str_longname = longname_item->str_value;

	AltiLab::DataObjectItem * address_item = dataobject->find_dataobjectitem("address");
	str_address = address_item->str_value;
	str_address_type = address_item->str_type;

	AltiLab::DataObjectItem * bitesize_item = dataobject->find_dataobjectitem("bitesize");
	str_bitesize = bitesize_item->str_value;

	AltiLab::DataObjectItem * modifiable_item = dataobject->find_dataobjectitem("modifiable");
	str_modifiable = modifiable_item->str_value;

	AltiLab::DataObjectItem * datatype_item = dataobject->find_dataobjectitem("datatype");
	str_datatype = datatype_item->str_value;

	AltiLab::DataObjectItem * choicetype_item = dataobject->find_dataobjectitem("choicetype");
	str_choicetype = choicetype_item->str_value;

	AltiLab::DataObjectItem * family_item = dataobject->find_dataobjectitem("family");
	str_family = family_item->str_value;
}
