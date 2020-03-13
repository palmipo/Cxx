#ifndef BIC_ELEMENT_H
#define BIC_ELEMENT_H

#include <string>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_BIC_DLL
#define BIC_DLL __declspec(dllexport)
#else
#define BIC_DLL __declspec(dllimport)
#endif
#else
#define BIC_DLL
#endif

namespace BIC 
{
	class BIC_DLL Element
	{
		public:
			Element(const std::string & = std::string());
			virtual ~Element();

			std::string str_tag;
			std::string str_register;
			std::string str_nb_register;
			std::string str_value;
			
			virtual void xml_read(xmlNode *);
	};
}
#endif
