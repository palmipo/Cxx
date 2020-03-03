#ifndef ALTILAB_PARSER_H
#define ALTILAB_PARSER_H

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
	class DataObjectCollection;
	class ALTILAB_DLL Parser
	{
		public:
			Parser(const std::string &);
			virtual ~Parser();

			DataObjectCollection * dataObject(const std::string & defaultgroupname="Functions", const std::string & defaultgroupname_id="PARAM", const std::string & defaultgroupname_name="Parameter");

		protected:
			void xml_device(xmlNode *);

			std::map < std::tuple < std::string, std::string, std::string >, DataObjectCollection * > map_data_object;
	};
}

#endif
