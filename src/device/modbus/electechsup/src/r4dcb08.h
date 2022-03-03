#ifndef R4DCB08_H
#define R4DCB08_H

#include <cstdint>

namespace Modbus
{
	class ModbusRtu;
	class R4DCB08
	{
		public:
			R4DCB08(uint8_t, ModbusRtu *);
			virtual ~R4DCB08();

			virtual void temperature(int8_t);
			virtual void allTemperature();

			virtual void temperatureCorrectionValue(int8_t);
			virtual void setTemperatureCorrectionValue(uint16_t, uint16_t);

			virtual void automaticTemperatureReport();
			virtual void setAutomaticTemperatureReport(int16_t);

			virtual void moduleAddress();
			virtual void setModuleAddress(uint16_t);

			virtual void baudRate();
			virtual void setBaudRate(uint16_t);
		
			virtual void resertFactory() const;

		protected:
			ModbusRtu * _rtu;
			uint8_t _module_address;
	};
}

#endif
