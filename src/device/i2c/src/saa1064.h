#ifndef __SAA1064_H__
#define __SAA1064_H__

#include "devicei2c.h"

class I2C;
class SAA1064 : public DeviceI2C
{
public:
	SAA1064(uint8_t adresse, I2C * i2c);

	void test_afficheurs (uint8_t valeur);
	void set_luminosity (uint8_t valeur);
	void afficher (const char *buffer, int32_t len);

	uint8_t status();

private:
	uint8_t _lumunosite;

private:
	uint8_t conversion_afficheur (const char digit_p);
};

#endif
