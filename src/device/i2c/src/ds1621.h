#ifndef __DS1621_H__
#define __DS1621_H__

#include "devicei2c.h"

class CtrlI2C;
class DS1621 : public DeviceI2C
{
	public:
		DS1621(uint8_t, CtrlI2C *);
		virtual ~DS1621();

		void conversion_unique (uint8_t);
		void setThermostatOutputSignal(uint8_t);
		void seuil_inferieur_thermostat(int8_t);
		void seuil_superieur_thermostat(int8_t);
		void debut_conversion();
		void fin_conversion();
		int8_t lecture_temperature();
};

#endif
