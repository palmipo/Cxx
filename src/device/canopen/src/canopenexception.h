#ifndef CAN_OPEN_EXCEPTION_H
#define CAN_OPEN_EXCEPTION_H

#include "pollexception.h"

namespace CAN
{
	class CANOpenException : public PollException
	{
		public:
			CANOpenException(const std::string & fichier, int32_t ligne, const std::string & error, PollDevice * device = 0)
			: PollException(fichier, ligne, error, device)
			{}
	};
}

#endif /* CAN_OPEN_EXCEPTION_H */
