#include "libaltilab/exception.h"
#include "log.h"
#include <libxml/xmlstring.h>
#include <iostream>

AltiLab::Exception::Exception(const std::string &file, uint32_t line, const std::string & msg)
: std::exception()
, _str(msg)
{
	//std::cout << file << line << "exception" << msg << std::endl;
	Log::getLogger()->error(file, line, msg);
}

AltiLab::Exception::~Exception()
{}

const char* AltiLab::Exception::what() const noexcept
{
	return _str.c_str();
}
