#include "towerfactory.h"

#include "xmlconfig.h"
#include "xmlinterface.h"
#include "xmlexception.h"

#include "genericdevice.h"
#include "rs232.h"
#include "rs232exception.h"

#include "socketcan.h"
#include "sockettcp.h"
#include "socketexception.h"

#include "modbustcp.h"
#include "modbusrtu.h"
#include "modbusmsgheader.h"

#include "ixxatcanatnet.h"
#include "ixxatusbcan.h"

#include "canopen.h"

#include "towerfactoryexception.h"

#include <thread>
#include <sstream>

#define MODBUS_TCP_PORT 502

TowerFactory * _instance = 0;

TowerFactory * TowerFactory::instance()
{
	if (!_instance)
	{
		_instance = new TowerFactory();
	}

	return _instance;
}

/*
 *
 */
TowerFactory::TowerFactory()
: PollFactory()
, xml_config(0)
, xml_interface(0)
{}

/*
 *
 */
TowerFactory::~TowerFactory()
{
	delete xml_interface;
	delete xml_config;

	std::map < std::tuple < std::string, std::string, std::string >, SmartCounter < TowerDevice * > >::iterator it_ctrl = ctrlMap.begin();
	while (it_ctrl != ctrlMap.end())
	{
		delete it_ctrl->second.instance();
		it_ctrl++;
	}

	std::map < std::string, SmartCounter < PollDevice * > >::iterator it_dev = ctrlDevice.begin();
	while (it_dev != ctrlDevice.end())
	{
		del(it_dev->second.instance()->handler());
		it_dev++;
	}
}

/*
 *
 */
void TowerFactory::fichier_configuration(const std::string & fichier_xml)
{
	xml_config = new XmlConfig(fichier_xml);
	xml_interface = new XmlInterface(xml_config->config()->fichier);
}

/*
 *
 */
XmlFactory * TowerFactory::xmlFactory()
{
	return xml_interface->getFactory();
}

/*
 *
 */
CAN::CANOpen * TowerFactory::getCANOpenCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	CAN::CANOpen * cnx = 0;
	try
	{
		cnx = (CAN::CANOpen *)getCtrl(
			type
			, type_id
			, iface
			);
	}
	catch(TowerFactoryException)
	{
		XmlControleur * can_ctrl_config = 0;
		XmlCanbus * can_ctrl = 0;
		if (type == "drive")
		{
			XmlDrive * drv = xml_interface->getFactory()->find_drive(type_id);
			can_ctrl = drv->getCanbus(iface);
			can_ctrl_config = xml_interface->getFactory()->find_ctrl(can_ctrl->str_ctrl_id);
		}
		else if (type == "plc")
		{
			XmlPlc * drv = xml_interface->getFactory()->find_plc(type_id);
			can_ctrl = drv->getCanbus(iface);
			can_ctrl_config = xml_interface->getFactory()->find_ctrl(can_ctrl->str_ctrl_id);
		}
		// else if (type == "ctrl")
		// {
			// can_ctrl_config = xml_interface->getFactory()->find_ctrl(type_id);
		// }
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "erreur parametre");
		}

		if (can_ctrl_config->str_type == "socketcan")
		{
			Socket::SocketCan * can = initSocketCan(can_ctrl_config->str_ctrl_id, can_ctrl_config->getCfg()->str_device);

			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(can_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				Ixxat::UsbCan * ixxat = new Ixxat::UsbCan(can_ctrl->getNodeId(), can);

				CAN::CANOpen * co = new CAN::CANOpen(can_ctrl->getNodeId(), ixxat, can);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(can_ctrl_config->str_ctrl_id, co);

				++(it->second);

				cnx = (CAN::CANOpen *)co;
			}
		}
		else if (can_ctrl_config->str_type == "ixxatcanatnet")
		{
			// ouverture de la socket vers la gateway can
			Socket::SocketTcp * s = initSocket(can_ctrl_config->str_ctrl_id, can_ctrl_config->getCfg()->str_ip, can_ctrl_config->getCfg()->getPort());
			
			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(can_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				// ouverture class can@net
				Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(can_ctrl->getNodeId(), s);

				// ouverture class CANOpen
				CAN::CANOpen * co = new CAN::CANOpen(can_ctrl->getNodeId(), ixxat, s);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(can_ctrl_config->str_ctrl_id, co);

				++(it->second);

				// initialisation du can@net apres enregistrement du PollDevice dans PollFactory
				ixxat->init(can_ctrl_config->getCfg()->getBaud());

				cnx = (CAN::CANOpen *)co;
			}
		}
		else
		{
			std::stringstream ss_exception;
			ss_exception << can_ctrl_config->str_type << " inconnu. erreur dans le fichier de configuration.";
			throw TowerFactoryException(__FILE__, __LINE__, ss_exception.str());
		}
	}

	// {
		// std::stringstream ss;
		// ss << "nb cnx : " << ctrlMap.size();
		// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	// }
	return cnx;
}

/*
 *
 */
void TowerFactory::closeCANOpenCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	closeCtrl(type, type_id, iface);
}

/*
 *
 */
CAN::Bus * TowerFactory::getCanCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	CAN::Bus * cnx = 0;
	try
	{
		cnx = (CAN::Bus *)getCtrl(
			type
			, type_id
			, iface
			);
	}
	catch(TowerFactoryException)
	{
		XmlControleur * can_ctrl_config = 0;
		XmlCanbus * can_ctrl = 0;
		if (type == "drive")
		{
			XmlDrive * drv = xml_interface->getFactory()->find_drive(type_id);
			can_ctrl = drv->getCanbus(iface);
			can_ctrl_config = xml_interface->getFactory()->find_ctrl(can_ctrl->str_ctrl_id);
		}
		else if (type == "plc")
		{
			XmlPlc * drv = xml_interface->getFactory()->find_plc(type_id);
			can_ctrl = drv->getCanbus(iface);
			can_ctrl_config = xml_interface->getFactory()->find_ctrl(can_ctrl->str_ctrl_id);
		}
		// else if (type == "ctrl")
		// {
			// can_ctrl_config = xml_interface->getFactory()->find_ctrl(type_id);
		// }
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "erreur parametre");
		}

		if (can_ctrl_config->str_type == "socketcan")
		{
			Socket::SocketCan * can = initSocketCan(can_ctrl_config->str_ctrl_id, can_ctrl_config->getCfg()->str_device);

			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(can_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				Ixxat::UsbCan * ixxat = new Ixxat::UsbCan(can_ctrl->getNodeId(), can);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(can_ctrl_config->str_ctrl_id, ixxat);
					++(it->second);

				cnx = (CAN::Bus *)ixxat;
			}
		}
		else if (can_ctrl_config->str_type == "ixxatcanatnet")
		{
			// ouverture de la socket vers la gateway can
			Socket::SocketTcp * s = initSocket(can_ctrl_config->str_ctrl_id, can_ctrl_config->getCfg()->str_ip, can_ctrl_config->getCfg()->getPort());
			
			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(can_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				// ouverture class can@net
				Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(can_ctrl->getNodeId(), s);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(can_ctrl_config->str_ctrl_id, ixxat);

				// increment du compteur d'instance
				++(it->second);

				// initialisation du can@net apres enregistrement du PollDevice dans PollFactory
				ixxat->init(can_ctrl_config->getCfg()->getBaud());

				cnx = (CAN::Bus *)ixxat;
			}
		}
		else
		{
			std::stringstream ss_exception;
			ss_exception << can_ctrl_config->str_type << " inconnu. erreur dans le fichier de configuration.";
			throw TowerFactoryException(__FILE__, __LINE__, ss_exception.str());
		}
	}

	return cnx;
}

/*
 *
 */
void TowerFactory::closeCanCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	closeCtrl(type, type_id, iface);
}

/*
 *
 */
Modbus::ModbusChannel * TowerFactory::getModbusCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	Modbus::ModbusChannel * cnx = 0;
	try
	{
		cnx = (Modbus::ModbusChannel *)getCtrl(type, type_id, iface);
	}
	catch(TowerFactoryException)
	{
		XmlModbus * modbus_ctrl = 0;
		XmlControleur * modbus_ctrl_config = 0;
		if (type == "drive")
		{
			XmlDrive * drv = xml_interface->getFactory()->find_drive(type_id);
			modbus_ctrl = drv->getModbus(iface);
			modbus_ctrl_config = xml_interface->getFactory()->find_ctrl(modbus_ctrl->str_ctrl_id);
		}
		else if (type == "plc")
		{
			XmlPlc * drv = xml_interface->getFactory()->find_plc(type_id);
			modbus_ctrl = drv->getModbus(iface);
			modbus_ctrl_config = xml_interface->getFactory()->find_ctrl(modbus_ctrl->str_ctrl_id);
		}
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "erreur parametre");
		}

		// {
			// std::stringstream ss;
			// ss << "modbus_ctrl->getSlaveAddr() = " << (int)modbus_ctrl->getSlaveAddr();
			// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		// }
		if (modbus_ctrl_config->str_type == "modbus_tcp")
		{
			Socket::SocketTcp * tcp = initSocket(modbus_ctrl_config->str_ctrl_id, modbus_ctrl_config->getCfg()->str_ip, modbus_ctrl_config->getCfg()->getPort() /*MODBUS_TCP_PORT*/);
			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(modbus_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				Modbus::ModbusTcp * modbus_tcp = new Modbus::ModbusTcp(modbus_ctrl->getSlaveAddr(), tcp);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(modbus_ctrl_config->str_ctrl_id, (TowerDevice *)modbus_tcp);
				
				++(it->second);

				cnx = (Modbus::ModbusChannel *)modbus_tcp;
			}
		}
		else if (modbus_ctrl_config->str_type == "modbus_rtu")
		{
			RS232 * serial = initSerial(
				modbus_ctrl_config->str_ctrl_id
				, modbus_ctrl_config->getCfg()->str_device
				, modbus_ctrl_config->getCfg()->getBaud()
				, modbus_ctrl_config->getCfg()->getStop()
				, modbus_ctrl_config->getCfg()->getParity()
			);

			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(modbus_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				Modbus::ModbusRtu * modbus_rtu = new Modbus::ModbusRtu(modbus_ctrl->getSlaveAddr(), serial);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(modbus_ctrl_config->str_ctrl_id, modbus_rtu);

				++(it->second);

				cnx = (Modbus::ModbusChannel *)modbus_rtu;
			}
		}
		else
		{
			std::stringstream ss_exception;
			ss_exception << modbus_ctrl_config->str_type << " inconnu. erreur dans le fichier de configuration.";
			throw TowerFactoryException(__FILE__, __LINE__, ss_exception.str());
		}
	}

	return cnx;
}

/*
 *
 */
void TowerFactory::closeModbusCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	closeCtrl(type, type_id, iface);
}

/*
 *
 */
GenericDevice * TowerFactory::getSocketCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	GenericDevice * cnx = 0;
	try
	{
		cnx = (GenericDevice *)getCtrl(type, type_id, iface);
	}
	catch(TowerFactoryException)
	{
		XmlControleur * modbus_ctrl_config = 0;
		if (type == "ctrl")
		{
			modbus_ctrl_config = xml_interface->getFactory()->find_ctrl(iface);
		}
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "i can't getCtrl enough");
		}

		GenericDevice * cnx = 0;
		if (modbus_ctrl_config->str_type == "socket_tcp")
		{
			Socket::SocketTcp * socket = initSocket(modbus_ctrl_config->str_ctrl_id, modbus_ctrl_config->getCfg()->str_ip, modbus_ctrl_config->getCfg()->getPort());

			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(modbus_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				cnx = new GenericDevice(socket);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter<TowerDevice *>(modbus_ctrl_config->str_ctrl_id, cnx);
				++(it->second);
			}
		}
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "i can't getCtrl enough");
		}
	}

	return cnx;
}

/*
 *
 */
void TowerFactory::closeSocketCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	closeCtrl(type, type_id, iface);
}

/*
 *
 */
GenericDevice * TowerFactory::getSerialCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	GenericDevice * cnx = 0;
	try
	{
		cnx = (GenericDevice *)getCtrl(type, type_id, iface);
	}
	catch(TowerFactoryException)
	{
		XmlControleur * modbus_ctrl_config = 0;
		if (type == "ctrl")
		{
			modbus_ctrl_config = xml_interface->getFactory()->find_ctrl(iface);
		}
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "i can't getCtrl enough");
		}

		if (modbus_ctrl_config->str_type == "serial")
		{
			RS232 * serial = initSerial(
				modbus_ctrl_config->str_ctrl_id
				, modbus_ctrl_config->getCfg()->str_device
				, modbus_ctrl_config->getCfg()->getBaud()
				, modbus_ctrl_config->getCfg()->getStop()
				, modbus_ctrl_config->getCfg()->getParity()
			);
			std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(modbus_ctrl_config->str_ctrl_id);
			if (it != ctrlDevice.end())
			{
				cnx = new GenericDevice(serial);

				ctrlMap[std::make_tuple(type, type_id, iface)] = SmartCounter < TowerDevice * >(modbus_ctrl_config->str_ctrl_id, cnx);
				++(it->second);
			}
		}
		else
		{
			throw TowerFactoryException(__FILE__, __LINE__, "i can't getCtrl enough");
		}
	}

	return cnx;
}

/*
 *
 */
void TowerFactory::closeSerialCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	closeCtrl(type, type_id, iface);
}

/*
 *
 */
TowerDevice * TowerFactory::getCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	std::map < std::tuple < std::string, std::string, std::string >, SmartCounter < TowerDevice * > >::iterator it = ctrlMap.find(std::make_tuple(type, type_id, iface));
	if (it != ctrlMap.end())
	{
		return it->second.instance();
	}

	std::stringstream ss_log;
	ss_log << "Aucune Connexion Ouverte Pour " << type << " / " << type_id << " / " << iface;
	throw TowerFactoryException(__FILE__, __LINE__, ss_log.str().c_str());
}

/*
 *
 */
void TowerFactory::closeCtrl(const std::string & type, const std::string & type_id, const std::string & iface)
{
	std::map < std::tuple < std::string, std::string, std::string >, SmartCounter < TowerDevice * > >::iterator it_ctrl = ctrlMap.find(std::make_tuple(type, type_id, iface));
	if (it_ctrl == ctrlMap.end())
	{
		std::stringstream ss_log;
		ss_log << "Aucune Connexion Ouverte Pour " << type << " / " << type_id << " / " << iface;
		throw TowerFactoryException(__FILE__, __LINE__, ss_log.str().c_str());
	}

	// suppression dans PollFactory
	std::map < std::string, SmartCounter < PollDevice * > >::iterator it_dev = ctrlDevice.find(it_ctrl->second.name());
	if (it_dev == ctrlDevice.end())
	{
		std::stringstream ss_log;
		ss_log << "Aucune Connexion Ouverte Pour " << type << " / " << type_id << " / " << iface;
		throw TowerFactoryException(__FILE__, __LINE__, ss_log.str().c_str());
	}

	--(it_dev->second);

	// suppression dans ctrlDevice
	if (it_dev->second.count() <= 0)
	{
		del(it_dev->second.instance()->handler());
		ctrlDevice.erase(it_dev);
	}
	
	//suppression dans ctrlMap
	delete it_ctrl->second.instance();
	ctrlMap.erase(it_ctrl);
}

/*
 *
 */
Socket::SocketTcp * TowerFactory::initSocket(const std::string & id, const std::string & ip, uint16_t port)
{
	Socket::SocketTcp * tcp = 0;
	std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(id);
	if (it != ctrlDevice.end())
	{
		tcp = (Socket::SocketTcp *)it->second.instance();
	}
	else
	{
		tcp = new Socket::SocketTcp();
		tcp->connexion(ip, port);
		tcp->setBufferSize(1024);
		add(tcp);
		SmartCounter < PollDevice * > cnt = SmartCounter < PollDevice * >(id, tcp);
		ctrlDevice[id] = cnt;
	}

	return tcp;
}

/*
 *
 */
Socket::SocketCan * TowerFactory::initSocketCan(const std::string & id, const std::string & device)
{
	Socket::SocketCan * can = 0;
	std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(id);
	if (it != ctrlDevice.end())
	{
		can = (Socket::SocketCan *)it->second.instance();
	}
	else
	{
		can = new Socket::SocketCan();
		can->connexion(device);
		add(can);
		SmartCounter < PollDevice * > smrt = SmartCounter < PollDevice * >(id, can);
		ctrlDevice[id] = smrt;
	}
	return can;
}

/*
 *
 */
RS232 * TowerFactory::initSerial(const std::string & id, const std::string & device, int32_t baudrate, int32_t stopbits, int32_t parity)
{
	RS232 * serial = 0;
	std::map < std::string, SmartCounter < PollDevice * > >::iterator it = ctrlDevice.find(id);
	if (it != ctrlDevice.end())
	{
		serial = (RS232 *)it->second.instance();
	}
	else
	{
		serial = new RS232(device);

		int32_t cparity;
		if (parity == 0)
			cparity = 'N';
		else if (parity == 1)
			cparity = 'E';
		else if (parity == 2)
			cparity = 'O';
		else
			throw TowerFactoryException(__FILE__, __LINE__, " parity : bad parameters");

		speed_t cbaudrate;
		if (baudrate == 1200)
			cbaudrate = B1200;
		else if (baudrate == 2400)
			cbaudrate = B2400;
		else if (baudrate == 4800)
			cbaudrate = B4800;
		else if (baudrate == 9600)
			cbaudrate = B9600;
		else if (baudrate == 19200)
			cbaudrate = B19200;
		else if (baudrate == 38400)
			cbaudrate = B38400;
		else
			throw TowerFactoryException(__FILE__, __LINE__, " baud rate : bad parameters");

		serial->setConfig(cbaudrate, 8, cparity, stopbits);
		serial->setInterCharacterTimer(1);

		add(serial);
		ctrlDevice[id] = SmartCounter < PollDevice * >(id, serial);
	}

	return serial;
}


/*
 *
 */
//~ void TowerFactory::close(PollDevice * device)
//~ {
	//~ if (device)
	//~ {
		//~ std::map < std::string, SmartCounter < PollDevice * > >::iterator it_dev = ctrlDevice.begin();
		//~ while (it_dev != ctrlDevice.end())
		//~ {
			//~ PollDevice * dev = it_dev->second.instance();
			//~ if (dev && (dev->handler() == device->handler()))
			//~ {
				//~ std::string id = it_dev->second.name();

				//~ std::map < std::tuple < std::string, std::string, std::string >, SmartCounter < TowerDevice * > >::iterator it_ctrl = ctrlMap.begin();
				//~ while (it_ctrl != ctrlMap.end())
				//~ {
					//~ if (it_ctrl->second.name() == id)
					//~ {
						//~ delete it_ctrl->second.instance();
						//~ ctrlMap.erase(it_ctrl);
						//~ it_ctrl = ctrlMap.begin();
					//~ }
					//~ else
					//~ {
						//~ it_ctrl++;
					//~ }
				//~ }

				//~ del(dev->handler());
				//~ ctrlDevice.erase(it_dev);
				//~ it_dev = ctrlDevice.begin();
			//~ }
			//~ else
			//~ {
				//~ it_dev++;
			//~ }
		//~ }
	//~ }
//~ }


/*
 *
 */
int32_t TowerFactory::actionIn(PollDevice * device)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	if (device)
	{
		try
		{
			// lecture sur le device
			int32_t length = device->actionIn();
			// if (length)
			{
				uint8_t data[512];
				int32_t len = device->read(data, 512);
				
				// envoie aux classes Modbus et CANOpen les donnees du controleur
				std::map < std::tuple < std::string, std::string, std::string >, SmartCounter < TowerDevice * > >::iterator it_ctrl = ctrlMap.begin();
				while (it_ctrl != ctrlMap.end())
				{
					// Log::getLogger()->debug(__FILE__, __LINE__, "element de ctrlMap !!!");
					if (device->handler() == it_ctrl->second.instance()->handler())
					{
						// Log::getLogger()->debug(__FILE__, __LINE__, "trouvé !!!");
						it_ctrl->second.instance()->actionIn(data, len);
					}

					it_ctrl++;
				}
			}
		}
		catch(PollException& e)
		{
			std::stringstream ss_log;
			ss_log << "exception levee : " << e.what();
			throw TowerFactoryException(__FILE__, __LINE__, ss_log.str().c_str());
		}
	}
}

/*
 *
 */
int32_t TowerFactory::actionOut(PollDevice * device)
{
	if (device)
	{
		try
		{
			device->actionOut();
		}
		catch(PollException& e)
		{
			std::stringstream ss_log;
			ss_log << "exception levee : " << e.what();
			throw TowerFactoryException(__FILE__, __LINE__, ss_log.str().c_str());
		}
	}
}

/*
 *
 */
int32_t TowerFactory::actionError(PollDevice * device)
{
	if (device)
	{
		try
		{
			// information au device du probleme
			device->actionError();

			// liberation du device / suppression de la liste des devices
			//~ close(device);
		}
		catch(PollException& e)
		{
			std::stringstream ss_log;
			ss_log << "exception levee : " << e.what();
			throw TowerFactoryException(__FILE__, __LINE__, ss_log.str().c_str());
		}
	}
}
