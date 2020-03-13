#ifndef BIC_EXCEPTION_H
#define BIC_EXCEPTION_H

#include <string>
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
	class BIC_DLL Exception : public std::exception
	{
		public:
			Exception(const std::string & file, uint32_t line, const std::string & msg);		
			virtual ~Exception();
			
			virtual const char* what()const noexcept;
			
		protected:
			std::string _str;
	};
}

#endif
