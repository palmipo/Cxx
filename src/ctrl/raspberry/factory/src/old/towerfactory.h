#ifndef TOWER_FACTORY_H
#define TOWER_FACTORY_H

#include "pollfactory.h"
#include "polldevice.h"
#include "towerdevice.h"
#include "smartcounter.h"
#include <cstdint>
#include <string>
#include <map>

namespace CAN
{
	class Bus;
	class CANOpen;
}
namespace Socket
{
	class SocketTcp;
	class SocketCan;
}
namespace Modbus
{
	class ModbusMsg;
	class ModbusChannel;
}

class GenericDevice;
class RS232;
class XmlFactory;
class XmlConfig;
class XmlInterface;
class TowerFactory : public PollFactory
{
		TowerFactory();
	
	public:
		static TowerFactory * instance();
		virtual ~TowerFactory();
	
		void fichier_configuration(const std::string & fichier_xml);
		virtual XmlFactory * xmlFactory();

		// methode utilisant le fichier interface.xml
		virtual CAN::CANOpen * getCANOpenCtrl(const std::string &, const std::string &, const std::string &);
		virtual void closeCANOpenCtrl(const std::string &, const std::string &, const std::string &);

		virtual Modbus::ModbusChannel * getModbusCtrl(const std::string &, const std::string &, const std::string &);
		virtual void closeModbusCtrl(const std::string &, const std::string &, const std::string &);

		virtual CAN::Bus * getCanCtrl(const std::string &, const std::string &, const std::string &);
		virtual void closeCanCtrl(const std::string &, const std::string &, const std::string &);

		virtual GenericDevice * getSerialCtrl(const std::string &, const std::string &, const std::string &);
		virtual void closeSerialCtrl(const std::string &, const std::string &, const std::string &);

		virtual GenericDevice * getSocketCtrl(const std::string &, const std::string &, const std::string &);
		virtual void closeSocketCtrl(const std::string &, const std::string &, const std::string &);

		virtual void closeCtrl(const std::string &, const std::string &, const std::string &);
		//~ virtual void close(PollDevice *);

	protected:
		// methode utilisant ctrlMap (bus : serial/socket_tcp/modbus_tcp/modbus_rtu/socketcan/ixxatcanatnet)
		virtual TowerDevice * getCtrl(const std::string &, const std::string &, const std::string &);

		// device
		virtual Socket::SocketTcp * initSocket(const std::string &, const std::string &, uint16_t);
		virtual Socket::SocketCan * initSocketCan(const std::string &, const std::string &);
		virtual RS232 * initSerial(const std::string &, const std::string &, int32_t, int32_t, int32_t);

	protected:
		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

	protected:
		XmlConfig * xml_config;
		XmlInterface * xml_interface;
	
		std::map < std::tuple < std::string, std::string, std::string >, SmartCounter < TowerDevice * > > ctrlMap;
		std::map < std::string, SmartCounter < PollDevice * > > ctrlDevice;
};

#endif /* TOWER_FACTORY_H */
