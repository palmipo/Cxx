#ifndef R4D3B16_H
#define R4D3B16_H

#include <cstdint>

namespace Modbus
{
	class ModbusRtu;
	class R4D3B16
	{
		public:
			R4D3B16(uint8_t, ModbusRtu *);
			virtual ~R4D3B16();
			virtual void open(uint8_t);
			virtual void close(uint8_t);
			virtual void toggle(uint8_t);

			virtual void get(uint16_t);
			virtual void getAll();

			virtual void openAll();
			virtual void closeAll();

		protected:
			ModbusRtu * _rtu;
			uint8_t _module_address;
	};
}

#endif
