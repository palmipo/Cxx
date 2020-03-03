#ifndef ALTILAB_GROUPITEM_H
#define ALTILAB_GROUPITEM_H

#include <cstdint>
#include <string>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>

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
	class ALTILAB_DLL GroupItem
	{
		public:
			GroupItem();
			virtual ~GroupItem();

			void xml_item(xmlNode *);

			std::string str_id;
	};
}

#endif
