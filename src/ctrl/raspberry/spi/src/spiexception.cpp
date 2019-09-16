#include "spiexception.h"
#include <sstream>
#include <errno.h>

SPIException::SPIException(const std::string & txt) throw()
{
	_err = errno;
	_txt = txt;
}

SPIException::~SPIException() throw()
{}

std::string SPIException::what() throw()
{
	std::stringstream buf;
	buf << "errno : " << _err << " : " << _txt;
	return buf.str();
}
