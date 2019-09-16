#ifndef MODBUS_EASY_H
#define MODBUS_EASY_H

#include "batratypes.h"
#include "modbuscontext.h"
#include <string>
#include <map>

namespace Modbus
{
    class ModbusFactory;
    class ModbusEasy
    {
        public:
			ModbusEasy(ModbusFactory *);
			virtual ~ModbusEasy();

			virtual void tcp(const std::string &, const std::string &);
			virtual void rtu(const std::string &, const std::string &, s32, s32, s32);
			virtual void close(const std::string &, const std::string &);
			virtual void close(const std::string &);
			virtual void closeAll();

			virtual u16 FC01(const std::string &, u8, u16, u16, u16, u8 *);
			virtual u16 FC02(const std::string &, u8, u16, u16, u16, u8 *);
			virtual u16 FC03(const std::string &, u8, u16, u16, u16, u8 *);
			virtual u16 FC04(const std::string &, u8, u16, u16, u16, u8 *);
			virtual u16 FC05(const std::string &, u8, u16, u16, u16, u8 *);
			virtual u16 FC06(const std::string &, u8, u16, u16, u16, u8 *);
			virtual u16 FC15(const std::string &, u8, u16, u16, u8 *, u16, u8 *);
			virtual u16 FC16(const std::string &, u8, u16, u16, u16 *, u16, u8 *);

			virtual u16 direct(const std::string &, u8 *, u16, s32, u16, u8 *);

			virtual void setReadIntervalTimeout(const std::string &, s32);
			virtual void setReadTotalTimeout(const std::string &, s32);
			virtual s32  getReadIntervalTimeout(const std::string &);
			virtual s32  getReadTotalTimeout(const std::string &);
        
        protected:
			s32 total_timeout;
			ModbusFactory * _factory;
			std::string _rtu_host;
    };
}

#endif
