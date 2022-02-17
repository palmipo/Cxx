#ifndef I2C_EXCEPTION_H
#define I2C_EXCEPTION_H

#include <exception>
#include <string>

class I2CException : public std::exception
{
	public:
		I2CException(const std::string & str) throw() : _err(str) {}
		virtual ~I2CException() throw() {}
		virtual const char* what() throw() { return _err.c_str(); }

	private:
		std::string _err;
};

#endif /* I2C_EXCEPTION_H */
