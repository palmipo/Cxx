#ifndef TOWER_FACTORY_EXCEPTION_H
#define TOWER_FACTORY_EXCEPTION_H

#include "pollexception.h"

class TowerFactoryException : public PollException
{
	public:
		TowerFactoryException(const std::string & fichier, int32_t ligne, const std::string & error)
		: PollException(fichier, ligne, error)
		{}
};

#endif /* TOWER_FACTORY_EXCEPTION_H */
