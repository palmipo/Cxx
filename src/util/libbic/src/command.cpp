#include "libbic/command.h"
#include "libbic/exception.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

BIC::Command::Command(const std::string & protocol)
: str_protocol(protocol)
{}

BIC::Command::~Command()
{}
