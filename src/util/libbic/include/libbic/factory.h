#ifndef BIC_FACTORY_H
#define BIC_FACTORY_H

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
	class Drive;
	class Plc;
	class Ctrl;
	class BIC_DLL Factory
	{
		public:
			static Factory * getInstance();
			virtual ~Factory();

			virtual void readConfigFile(const std::string &);

			virtual Plc *   find_plc   (std::string);
			virtual Drive * find_drive (std::string);

			virtual Ctrl * find_ctrl(std::string);
			virtual void   add_ctrl(Ctrl *);

			virtual void xml_ctrl(xmlNode *);
			virtual void xml_drives(xmlNode *);
			virtual void xml_plc(xmlNode *);

			std::map < std::string , Drive * > map_drive;
			std::map < std::string , Plc * > map_plc;
			std::map < std::string , Ctrl * > map_ctrl;

		private:
			Factory();
	};
}

#endif
