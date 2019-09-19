#include "hc_sr04.h"
#include "log.h"
#include <sstream>
#include <thread>

int main(int argc,char **argv)
{
	HC_SR04 telemetre(17, 18);

	for (int32_t i=0; i<10; ++i)
	{
		int64_t dst = telemetre.distance();
		
		std::stringstream ss;
		ss << "distance : " << dst << " mm.";
		Log::getLogger()->info(__FILE__, __LINE__, ss.str());

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}
