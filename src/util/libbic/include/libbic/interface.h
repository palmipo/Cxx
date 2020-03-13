#ifndef BIC_INTERFACE_H
#define BIC_INTERFACE_H

#include <string>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <exception>

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
	class BIC_DLL Interface
	{
		public:
			Interface(const std::string & fichier_xml);
			virtual ~Interface();

			// Factory factory;

			void xml_read(xmlNode * a_node);
	};
}

#endif
