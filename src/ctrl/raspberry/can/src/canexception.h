#ifndef CAN_EXCEPTION_H
#define CAN_EXCEPTION_H

#include "pollexception.h"

namespace CAN
{
	class Exception : public PollException
	{
		public:
			Exception(const std::string & fichier, int32_t ligne, int32_t error)
			: PollException(fichier, ligne, error)
			{}
			Exception(const std::string & fichier, int32_t ligne, const std::string & error)
			: PollException(fichier, ligne, error)
			{}
	};
}

#endif /* CAN_EXCEPTION_H */
