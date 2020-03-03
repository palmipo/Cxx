#ifndef ALTILAB_GROUPLIST_H
#define ALTILAB_GROUPLIST_H

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
	class Group;
	class ALTILAB_DLL GroupList
	{
		public:
			GroupList();
			virtual ~GroupList();

			void xml_grouplist(xmlNode *);

			std::string str_name;
			Group * find_group(const std::string &);

		protected:
			std::map < std::string, Group * > map_group;
	};
}

#endif
