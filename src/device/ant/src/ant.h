/*
 * /etc/udev/rules.d/garmin-ant2.rules
 * SUBSYSTEM=="usb", ATTRS{idVendor}=="0fcf", ATTRS{idProduct}=="1009", RUN+="/sbin/modprobe usbserial vendor=0x0fcf product=0x1009", MODE="0666", OWNER="root", GROUP="root"
 */

#ifndef ANT_ANT_H
#define ANT_ANT_H

#include "pollfactory.h"
#include <cstdint>
#include <map>
/* GARMIN NETWORK KEY */
/* B9:A5:21:FB:BD:72:C3:45 */

class RS232;
namespace ANT
{
	class Ant : public PollFactory
	{
		public:
			Ant(const std::string &);
			virtual ~Ant();

			/*
			 * CONFIG MESSAGES
			 */
			void unassignChannel(uint8_t);
			void assignChannel(uint8_t, uint8_t, uint8_t, uint8_t);
			void channelId(uint8_t, uint16_t, uint8_t, uint8_t);
			void channelPeriod(uint8_t, uint16_t);
			void searchTimeout(uint8_t, uint8_t);
			void channelRfFrequency(uint8_t, uint8_t);
			void setNetworkKey(uint8_t, uint8_t *);
			void transmitPower(uint8_t);
			void searchWaveForm(uint8_t, uint16_t);
			void addChannelIdToList(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
			void addEncryptionIdToList(uint8_t, uint8_t, uint8_t);
			// config id list
			void configEncryptionIdList(uint8_t, uint8_t, uint8_t);
			void setChannelTransmitPower(uint8_t, uint8_t);
			void lowPrioritySearchTimeout(uint8_t, uint8_t);
			void serialNumberSetChannelID(uint8_t, uint8_t, uint8_t);
			void enableExtRXMessages(uint8_t);
			void enableLED(uint8_t);
			void crystalEnable();
			void libConfig(uint8_t);
			void frequencyAgility(uint8_t, uint8_t, uint8_t, uint8_t);
			void proximitySearch(uint8_t, uint8_t);
			void configureEventBuffer(uint8_t, uint16_t, uint16_t);
			void channelSearchPriority(uint8_t, uint8_t);
			void set128BitNetworkKey(uint8_t, uint8_t*);
			void highDutySearch(uint8_t, uint16_t);
			void configureAdvancedBurst(uint8_t, uint8_t, uint32_t, uint32_t, uint8_t);
			void configureEventFilter(uint16_t);
			void configureSelectiveDataUpdates(uint8_t, uint8_t);
			void setSelectiveDataUpdateMask(uint8_t, uint8_t*);
			void configureUserNvm(uint16_t, uint8_t *, int32_t);
			void enableSingleChannelEncryption(uint8_t, uint8_t, uint8_t, uint8_t);
			void setEncryptionKey(uint8_t, uint8_t*);
			void setEncryptionInfo(uint8_t, uint8_t*);
			void channelSearchSharing(uint8_t, uint8_t);
			void loadStoreEncryptionKey(uint8_t, uint8_t, uint8_t*);
			void setUsbDescriptorString(uint8_t, uint8_t*, uint8_t);

			/*
			 * NOTIFICATIONS
			 */
			virtual void startupMessageRecv(uint8_t) = 0; // 0x6f
			virtual void serialErrorMessageRecv(uint8_t) = 0; // 0xae
			 
			/*
			 * CONTROL MESSAGES
			 */
			virtual void resetSystem();
			virtual void openChannel(uint8_t);
			virtual void closeChannel(uint8_t);
			virtual void requestMessage(uint8_t, uint8_t, uint8_t *, uint8_t);
			virtual void openRxScanMode(uint8_t*, uint16_t);
			virtual void sleepMessage();

			/*
			 * DATA MESSAGES
			 */
			virtual void broadcastData(uint8_t, uint8_t*, uint16_t);
			virtual int32_t broadcastDataRecv(uint8_t*, int32_t) = 0;
			virtual void acknowledgedData(uint8_t, uint8_t *, uint16_t);
			virtual int32_t acknowledgedDataRecv(uint8_t*, int32_t) = 0;
			virtual void burstTransferData(uint8_t, uint8_t *, uint16_t);
			virtual int32_t burstTransfertDataRecv(uint8_t*, int32_t) = 0;
			virtual void advancedBurstData(uint8_t, uint8_t *, uint8_t);
			virtual int32_t advancedBurstDataRecv(uint8_t*, int32_t) = 0;

			/*
			 * CHANNEL MESSAGES
			 */
			virtual int32_t channelMessagesRecv(uint8_t *, int32_t) = 0; // 0x40
			
			/*
			 * REQUESTED RESPONSE MESSAGES
			 */
			virtual void channelStatusRecv(uint8_t, uint8_t) = 0;
			virtual void channelIdRecv(uint8_t, uint16_t, uint8_t, uint8_t) = 0;
			virtual void antVersionRecv(uint8_t *, int32_t) = 0;
			virtual void capabilitiesRecv(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t) = 0; // 0x54
			virtual void serialNumberRecv(uint32_t) = 0;
			virtual void eventBufferConfigurationRecv(uint8_t, uint16_t, uint16_t) = 0; // 0x74
			virtual void advancedBurstCapabilitiesRecv(uint8_t, uint32_t) = 0; // 0x78
			virtual void advancedBurstCurrentConfigurationRecv(uint8_t, uint8_t, uint32_t, uint32_t, uint8_t) = 0; // 0x78
			virtual void eventFilterRecv(uint16_t) = 0; // 0x79
			virtual void selectiveDataUpdateMaskSettingRecv(uint8_t, uint8_t *) = 0; // 0x7b
			virtual void userNvmRecv(uint8_t*) = 0; // 0x7c
			virtual void encryptionModeParametersRecv(uint8_t, uint8_t*) = 0; // 0x7d
			
			/*
			 * TEST MODE
			 */
			virtual void cwInit();
			virtual void cwTest(uint8_t, uint8_t);
			
			/*
			 * EXTENDED DATA MESSAGES
			 */
			virtual void extendedBroadcastData(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*);
			virtual int32_t extendedBroadcastDataRecv(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*) = 0; // 0x5d
			virtual void extendedAcknowledgedData(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*);
			virtual int32_t extendedAcknowledgedDataRecv(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*) = 0; // 0x5e
			virtual void extendedBurstData(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*);
			virtual int32_t extendedBurstDataRecv(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t*) = 0; // 0x5f


		protected:
			virtual int32_t send(uint8_t, uint8_t *, int32_t);
			virtual int32_t recv(const uint8_t *, int32_t);
			virtual uint8_t checksum(uint8_t *, uint8_t);

			int32_t _handler;
			virtual int32_t actionIn(PollDevice*);
			virtual int32_t actionOut(PollDevice*);
			virtual int32_t actionError(PollDevice*);
	};
}

#endif /* ANT_H */
