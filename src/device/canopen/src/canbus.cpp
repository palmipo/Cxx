#include "canopen.h"

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

/* constructeur socket client */
CanBus::CanBus()
: PollDevice()
{}

CanBus::~CanBus()
{}

void CanBus::connexion(const std::string & cnx)
{}

int32_t CanBus::write(uint8_t * msg, int32_t length)
{}

int32_t CanBus::read(uint8_t * msg, int32_t length)
{}

void CanBus::actionError()
{}

void CanBus::actionIn()
{}

void CanBus::actionOut()
{}
