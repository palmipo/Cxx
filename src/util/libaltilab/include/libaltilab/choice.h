#ifndef ALTILAB_CHOICE_H
#define ALTILAB_CHOICE_H

#include <cstdint>
#include <string>
// #include <map>
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
	class ALTILAB_DLL Choice
	{
		public:
			Choice();
			virtual ~Choice();

			std::string str_description;
			std::string str_value;
			std::string str_choice;

			void xml_choice(xmlNode *);
	};
}

#endif
