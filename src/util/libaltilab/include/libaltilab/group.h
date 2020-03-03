#ifndef ALTILAB_GROUP_H
#define ALTILAB_GROUP_H

#include <cstdint>
#include <string>
#include <map>
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
	class GroupItem;
	class ALTILAB_DLL Group
	{
		public:
			Group();
			virtual ~Group();

			void xml_group(xmlNode *);

			std::string str_name;
			GroupItem * find_groupitem(const std::string &);

		protected:
			std::map < std::string, GroupItem * > map_goupItem;
	};
}

#endif
