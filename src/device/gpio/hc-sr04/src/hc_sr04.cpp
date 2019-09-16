#include "hc_sr04.h"
#include <thread>

HC_SR04::HC_SR04(Gpio * out, Gpio * in)
{}

int32_t HC_SR04::distance()
{
	uint8_t valeur;

	valeur = 1;
	out->write(&valeur, 1);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	valeur = 0;
	out->write(&valeur, 1);
}
