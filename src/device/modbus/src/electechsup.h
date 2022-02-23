#ifndef ELECTECHSUP_H
#define ELECTECHSUP_H

#include "modbusfactory.h"

namespace Modbus
{
	class ElecTechSup : public ModbusFactory
	{
		public:
			ElecTechSup();
			virtual ~ElecTechSup();
		
		protected:
			virtual int32_t actionIn(PollDevice*);
		
		protected:
			R4DCB08 * _can;
			R4D3B16 * _output;
			N4DIH32 * _input;
	};
}

#endif
