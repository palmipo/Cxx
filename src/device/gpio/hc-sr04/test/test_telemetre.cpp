#include "hc_sr04.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <chrono>

void scrute(HC_SR04 * telemetre, int32_t * fin)
{
	while(! *fin)
	{
		telemetre->scrute(1000);
	}
}

int main(int argc,char **argv)
{
	int32_t fin = 0;
	HC_SR04 telemetre(17, 18);
	std::thread t(scrute, &telemetre, &fin);
	t.detach();
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
	fin = 1;
	return 0;
}
