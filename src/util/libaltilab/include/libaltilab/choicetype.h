#ifndef ALTILAB_CHOICETYPE_H
#define ALTILAB_CHOICETYPE_H

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
	class Choice;
	class ALTILAB_DLL ChoiceType
	{
		public:
			ChoiceType();
			virtual ~ChoiceType();

			std::string str_id;
			
			Choice * find_value(const std::string &);
			Choice * find_choice(const std::string &);

			void xml_choicetype(xmlNode *);

		protected:
			std::map < std::string, Choice * > map_choices;
	};
}

#endif
