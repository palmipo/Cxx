#ifndef ALTILAB_EXCEPTION_H
#define ALTILAB_EXCEPTION_H

#include <string>
#include <exception>

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
	class ALTILAB_DLL Exception : public std::exception
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
