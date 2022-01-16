#ifndef R4DCB08_H
#define R4DCB08_H

#include <cstdint>

namespace Modbus
{
	class ModbusRtu;
	class R4DCB08
	{
	public:
		R4DCB08(ModbusRtu *);
		~R4DCB08();

		int16_t temperature(int8_t);

		int16_t temperatureCorrectionValue(int8_t);
		void    setTemperatureCorrectionValue(uint16_t, uint16_t);

		int16_t automaticTemperatureReport();
		void    setAutomaticTemperatureReport(int16_t);

		int16_t moduleAddress();
		void    setModuleAddress(uint16_t);

		int16_t baudRate();
		void    setBaudRate(uint16_t);

	protected:
		ModbusRtu * _rtu;
	};
}

#endif
