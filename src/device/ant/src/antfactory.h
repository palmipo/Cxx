#ifndef ANT_FACTORY_H
#define ANT_FACTORY_H

#include "ant.h"
#include <cstdint>
#include <map>

class RS232;
namespace ANT
{
	class Profile;
	class Tempe;
	class HeartRate;
	class SpeedCadence;
	//~ class Ctrl;
	class AntFactory : public Ant
	{
		public:
			AntFactory(const std::string &);
			virtual ~AntFactory();
			
			Tempe * addTempeMonitor();
			HeartRate * addHRMonitor();
			SpeedCadence * addSpeedCadenceMonitor();
			//~ Ctrl * addVideoCtrlMaster();

			Profile * get(uint8_t);
			void close(uint8_t);

		protected:
			virtual void networkKeyRecv(uint8_t);
			virtual void transmitPowerEventRecv(uint8_t);

		protected:
			/*
			 * NOTIFICATIONS
			 */
			virtual void startupMessageRecv(uint8_t); // 0x6f
			virtual void serialErrorMessageRecv(uint8_t); // 0xae

			/*
			 * DATA MESSAGES
			 */
			virtual int32_t broadcastDataRecv(uint8_t*, int32_t);
			virtual int32_t acknowledgedDataRecv(uint8_t*, int32_t);
			virtual int32_t burstTransfertDataRecv(uint8_t*, int32_t);
			virtual int32_t advancedBurstDataRecv(uint8_t*, int32_t);

			/*
			 * CHANNEL MESSAGES
			 */
			virtual int32_t channelMessagesRecv(uint8_t *, int32_t); // 0x40
			
			/*
			 * REQUESTED RESPONSE MESSAGES
			 */
			virtual void channelStatusRecv(uint8_t, uint8_t);
			virtual void channelIdRecv(uint8_t, uint16_t, uint8_t, uint8_t);
			virtual void antVersionRecv(uint8_t *, int32_t);
			virtual void capabilitiesRecv(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t); // 0x54
			virtual void serialNumberRecv(uint32_t);
			virtual void eventBufferConfigurationRecv(uint8_t, uint16_t, uint16_t); // 0x74
			virtual void advancedBurstCapabilitiesRecv(uint8_t, uint32_t); // 0x78
			virtual void advancedBurstCurrentConfigurationRecv(uint8_t, uint8_t, uint32_t, uint32_t, uint8_t); // 0x78
			virtual void eventFilterRecv(uint16_t); // 0x79
			virtual void selectiveDataUpdateMaskSettingRecv(uint8_t, uint8_t *); // 0x7b
			virtual void userNvmRecv(uint8_t*); // 0x7c
			virtual void encryptionModeParametersRecv(uint8_t, uint8_t*); // 0x7d
			
			/*
			 * EXTENDED DATA MESSAGES
			 */
			virtual int32_t extendedBroadcastDataRecv(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*); // 0x5d
			virtual int32_t extendedAcknowledgedDataRecv(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*); // 0x5e
			virtual int32_t extendedBurstDataRecv(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*); // 0x5f

		protected:
			uint8_t _last_chanel_number;
			uint8_t _network_number;
			std::map < uint8_t, Profile * > _devices;
	};
}

#endif /* ANT_FACTORY_H */
