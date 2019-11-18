#include "log.h"

int main(int argc, char **argv)
{
	Log * logger = Log::getLogger();
	logger->DEBUG(__FILE__, __LINE__, "Hello World ...");
	return 0;
}
