#ifndef MODBUSCODEC_H
#define MODBUSCODEC_H

namespace Modbus
{
	class ModbusCodec
	{
		ModbusCodec();
		virtual ~ModbusCodec();
		
		ModbusRtuMsg* decode(Modbus::ModbusRtu *);
	};
}

void Modbus::ModbusCodec::decode(Modbus::ModbusRtu * rtu)
{
	s32 cpt=0;

	ModbusRtuMsg entete, *msgobj=0;
	entete.decode(msg, len);
	
	if (entete.errorCode())
	{
		msgobj = new Modbus::ModbusRtuMsgError();
	}
	
	else if (entete.functionCode() == 0x01)
	{
		msgobj = new Modbus::ModbusRtuMsgFC01();
	}
	
	else if (entete.functionCode() == 0x02)
	{
		msgobj = new Modbus::ModbusRtuMsgFC02();
	}
	
	else if (entete.functionCode() == 0x03)
	{
		msgobj = new Modbus::ModbusRtuMsgFC03();
	}
	
	else if (entete.functionCode() == 0x04)
	{
		msgobj = new Modbus::ModbusRtuMsgFC04();
	}
	
	else if (entete.functionCode() == 0x05)
	{
		msgobj = new Modbus::ModbusRtuMsgFC05();
	}
	
	else if (entete.functionCode() == 0x06)
	{
		msgobj = new Modbus::ModbusRtuMsgFC06();
	}
	
	else if (entete.functionCode() == 0x08)
	{
		msgobj = new Modbus::ModbusRtuMsgFC08();
	}
	
	else if (entete.functionCode() == 0x0B)
	{
		msgobj = new Modbus::ModbusRtuMsgFC11();
	}
	
	else if (entete.functionCode() == 0x10)
	{
		msgobj = new Modbus::ModbusRtuMsgFC16();
	}
	
	else if (entete.functionCode() == 0x17)
	{
		msgobj = new Modbus::ModbusRtuMsgFC23();
	}
	
	else if (entete.functionCode() == 0x2B)
	{
		msgobj = new Modbus::ModbusRtuMsgFC43();
	}

	if (!msgobj)
	{
		std::stringstream ss;
		ss << "MODBUS : decodage trame non implemente " << (int)entete.functionCode();
		throw Modbus::ModbusException(ss.str());
	}

	cpt += msgobj->decode(msg, len);

	// crc du message
	cpt += rtu->recvDirectly(msg+cpt, 2, data);
	u16 crc = msg[cpt - 1] | (msg[cpt - 2] << 8);

	// calcul du crc du message
	u16 ccrc = rtu->calcul_crc(msg, cpt - 2);

	if (crc != ccrc)
	{
		throw Modbus::ModbusException("calcul CRC different de celui de la trame recu");
	}
	else
	{
		if (rtu->_callbackDirectResponse)
		{
			rtu->_callbackDirectResponse((u8*)msg, cpt, rtu->_dataDirectResponse);
		}
	}
}

#endif
