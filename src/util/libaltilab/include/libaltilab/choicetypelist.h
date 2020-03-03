#ifndef ALTILAB_CHOICETYPELIST_H
#define ALTILAB_CHOICETYPELIST_H

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
	class ChoiceType;
	class ALTILAB_DLL ChoiceTypeList
	{
		public:
			ChoiceTypeList();
			virtual ~ChoiceTypeList();
		
			void xml_choicetypelist(xmlNode *);
			ChoiceType * find_choicetype(const std::string &);

		protected:
			std::map < std::string, ChoiceType * > map_choices;
	};
}

#endif
