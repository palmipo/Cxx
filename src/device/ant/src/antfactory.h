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

			/*
			 * NOTIFICATIONS
			 */
			virtual int32_t startupMessageRecv(uint8_t *, int32_t); // 0x6f
			virtual int32_t serialErrorMessageRecv(uint8_t *, int32_t); // 0xae

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
			virtual int32_t channelStatusRecv(uint8_t *, int32_t);
			virtual int32_t channelIdRecv(uint8_t *, int32_t);
			virtual int32_t antVersionRecv(uint8_t *, int32_t);
			virtual int32_t capabilitiesRecv(uint8_t *, int32_t); // 0x54
			virtual int32_t serialNumberRecv(uint8_t *, int32_t);
			virtual int32_t eventBufferConfigurationRecv(uint8_t *, int32_t); // 0x74
			virtual int32_t advancedBurstCapabilitiesRecv(uint8_t *, int32_t); // 0x78
			virtual int32_t advancedBurstCurrentConfigurationRecv(uint8_t *, int32_t); // 0x78
			virtual int32_t eventFilterRecv(uint8_t *, int32_t); // 0x79
			virtual int32_t selectiveDataUpdateMaskSettingRecv(uint8_t *, int32_t ); // 0x7b
			virtual int32_t userNvmRecv(uint8_t *, int32_t); // 0x7c
			virtual int32_t encryptionModeParametersRecv(uint8_t *, int32_t); // 0x7d
			
			/*
			 * EXTENDED DATA MESSAGES
			 */
			virtual int32_t extendedBroadcastDataRecv(uint8_t *, int32_t); // 0x5d
			virtual int32_t extendedAcknowledgedDataRecv(uint8_t *, int32_t); // 0x5e
			virtual int32_t extendedBurstDataRecv(uint8_t *, int32_t); // 0x5f


		protected:
			virtual void networkKeyRecv(uint8_t);
			virtual void transmitPowerEventRecv(uint8_t);

		protected:
			uint8_t _last_chanel_number;
			std::map < uint8_t, Profile * > _devices;
	};
}

#endif /* ANT_FACTORY_H */
