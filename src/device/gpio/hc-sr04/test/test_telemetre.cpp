#include "hc_sr04.h"
#include "log.h"
#include <sstream>

int main(int argc,char **argv)
{
	HC_SR04 telemetre(18, 28);
	int64_t dst = telemetre.distance();
	
	std::stringstream ss;
	ss << "distance : " << dst;
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	return 0;
}
