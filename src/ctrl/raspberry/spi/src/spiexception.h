#ifndef SPI_EXCEPTION_H
#define SPI_EXCEPTION_H

#include <exception>
#include <string>

class SPIException : public std::exception
{
public:
	SPIException(const std::string &) throw();
	virtual ~SPIException() throw();

	virtual std::string what() throw();

private:
	int _err;
	std::string _txt;
};

#endif /* SPI_EXCEPTION_H */
