#ifndef SPI_EXCEPTION_H
#define SPI_EXCEPTION_H

#include <exception>
#include <string>
#include <sstream>
#include <errno.h>

class SPIException : public std::exception
{
public:
	SPIException(const std::string & txt) throw()
	{
		_err = errno;
		_txt = txt;
	}

	virtual ~SPIException() throw()
	{}

	virtual std::string what() throw()
	{
		std::stringstream buf;
		buf << "errno : " << _err << " : " << _txt;
		return buf.str();
	}

private:
	int _err;
	std::string _txt;
};

#endif /* SPI_EXCEPTION_H */
