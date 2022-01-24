#ifndef POLLEXCEPTION_H
#define POLLEXCEPTION_H

#include "log.h"
#include "polldevice.h"
#include <exception>
#include <string>
#include <cstring>

class PollException : public std::exception
{
	public:
		PollException(const std::string & fichier, int32_t ligne, int32_t numerror, PollDevice * device = 0)
		{
			_error = strerror(numerror);
			_device = device;
			Log::getLogger()->error(fichier, ligne, _error);
		}

		PollException(const std::string & fichier, int32_t ligne, const std::string & err, PollDevice * device = 0)
		{
			_error = err;
			_device = device;
			Log::getLogger()->error(fichier, ligne, _error);
		}

		virtual const char* what() const noexcept
		{
			return _error.c_str();
		}

		virtual PollDevice * device()
		{
			return _device;
		}

	protected:
		std::string _error;
		PollDevice * _device;
};

#endif /* POLLEXCEPTION_H */
