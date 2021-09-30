#include "hc_sr04.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <chrono>

int main(int argc,char **argv)
{
	HC_SR04 telemetre(17, 18);
	telemetre.start(2);

	for (int32_t i=0; i<1000; ++i)
	{
		if (!telemetre.status())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			double dst = telemetre.distance();
			std::stringstream ss;
			ss << "distance : " << dst << " mm.";
			Log::getLogger()->info(__FILE__, __LINE__, ss.str());
		}
	}
	telemetre.stop();

	return 0;
}
