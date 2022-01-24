#ifndef N4DIH32_H
#define N4DIH32_H

#include <cstdint>

namespace Modbus
{
	class ModbusRtu;
	class N4DIH32
	{
		public:
		N4DIH32(uint8_t, ModbusRtu *);
		virtual ~N4DIH32();

		virtual void get();
		virtual void getAll();

		virtual void setTempoAutomaticReporting(uint8_t);
		virtual void setAllAutomaticReporting(uint8_t);

		virtual void baudRate();
		virtual void setBaudRate(uint16_t);

		virtual void resetFactory();

		protected:
			ModbusRtu * _rtu;
			uint8_t _module_address;
	};
}

#endif

