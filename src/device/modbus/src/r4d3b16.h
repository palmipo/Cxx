#ifndef R4D3B16_H
#define R4D3B16_H

#include <cstdint>

namespace Modbus
{
	class ModbusRtu;
	class R4D3B16
	{
		public:
			R4D3B16(ModbusRtu *);
			virtual ~R4D3B16();
			void open(uint8_t);
			void close(uint8_t);
			void toggle(uint8_t);

			uint16_t read(uint16_t);

			void openAll();
			void closeAll();

		protected:
			ModbusRtu * _rtu;
	};
}

#endif
