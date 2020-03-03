#ifndef ALTILAB_DATAOBJECT_H
#define ALTILAB_DATAOBJECT_H

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
	class DataObjectItem;
	class ALTILAB_DLL DataObject
	{
		public:
			DataObject();
			virtual ~DataObject();

			void xml_dataobject(xmlNode *);

			std::string str_id;

			DataObjectItem * find_dataobjectitem(const std::string &);

		protected:
			std::map < std::string, DataObjectItem * > map_item;
	};
}

#endif
