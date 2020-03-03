#ifndef ALTILAB_DATAOBJECTCOLLECTION_H
#define ALTILAB_DATAOBJECTCOLLECTION_H

#include <cstdint>
#include <string>
#include <map>
#include <list>
#include <libxml/parser.h>
#include <libxml/tree.h>
// #include <exception>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_ALTILAB_DLL
#define ALTILAB_DLL __declspec(dllexport)
#else
#define ALTILAB_DLL __declspec(dllimport)
#endif
#else
#define ALTILAB_DLL
#endif

namespace AltiLab
{
	class DataObject;
	class DataObjectList;
	class ChoiceType;
	class ChoiceTypeList;
	class GroupList;
	class ALTILAB_DLL DataObjectCollection
	{
		public:
			DataObjectCollection();
			virtual ~DataObjectCollection();

			uint32_t cpu();

			DataObject * find_dataobject(const std::string &);
			ChoiceType * find_choicetype(const std::string &);
			GroupList * find_grouplist(const std::string &);

			void xml_dataobjectcollection(xmlNode *);

			std::string str_cpu;
			std::string str_defaultgroupname;
			std::string str_id;
			std::string str_name;
			
		protected:
			std::list < DataObjectList * > list_dataobjectlist;
			std::list < ChoiceTypeList * > list_choicetypelist;
			std::map < std::string, GroupList * > map_grouplist;
	};
}

#endif
