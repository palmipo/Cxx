#include "hc_sr04.h"
#include "log.h"
#include <sstream>

int main(int argc,char **argv)
{
	HC_SR04 telemetre(17, 18);
	int64_t dst = telemetre.distance();
	//~ telemetre.scrute(1000);
	//~ telemetre.scrute(1000);
	
	std::stringstream ss;
	ss << "distance : " << dst << " mm.";
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	return 0;
}
