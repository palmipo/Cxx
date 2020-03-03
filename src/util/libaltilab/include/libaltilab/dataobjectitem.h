#ifndef ALTILAB_DATAOBJECTITEM_H
#define ALTILAB_DATAOBJECTITEM_H

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
	class ALTILAB_DLL DataObjectItem
	{
		public:
			DataObjectItem();
			virtual ~DataObjectItem();

			void xml_item(xmlNode *);

			std::string str_type;
			std::string str_name;
			std::string str_value;
	};
}

#endif
