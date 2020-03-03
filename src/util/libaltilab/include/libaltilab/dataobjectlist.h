#ifndef ALTILAB_DATAOBJECTLIST_H
#define ALTILAB_DATAOBJECTLIST_H

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
	class DataObject;
	class ALTILAB_DLL DataObjectList
	{
		public:
			DataObjectList();
			virtual ~DataObjectList();

			uint32_t cpu();

			DataObject * find_dataobject(const std::string & registre_id);

			void xml_dataobjectlist(xmlNode *);

		protected:
			std::map < std::string, DataObject * > map_dataobject;
	};
}

#endif
