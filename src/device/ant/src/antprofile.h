#ifndef ANT_PROFILE_H
#define ANT_PROFILE_H

#include <cstdint>

namespace ANT
{
	class Ant;
	class Profile
	{
		public:
			Profile(uint8_t, Ant *);
			virtual ~Profile();

			virtual void init() = 0;
			virtual uint8_t channelNumber();
			
			// antprofilesend.h
			virtual void requestDataPage(uint8_t);
			virtual void modeSettingsPage(uint8_t);
			virtual void sendManufacturerIdentification();
			virtual void sendProductInformation();
			virtual void sendBatteryStatus();
			virtual void sendTimeDate(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
			virtual void sendMemory();

			/*
			 * resultat de commandes
			 */
			virtual void channelEventRecv(uint8_t, uint8_t);

			virtual void unassignedChannelEventRecv(uint8_t) = 0;
			virtual void assignedChannelEventRecv(uint8_t) = 0;
			virtual void channelPeriodEventRecv(uint8_t) = 0;
			virtual void searchTimeoutEventRecv(uint8_t) = 0;
			virtual void channelRfFrequencyEventRecv(uint8_t) = 0;
			virtual void searchWaveformEventRecv(uint8_t) = 0;
			virtual void channelOpenedEventRecv(uint8_t) = 0;
			virtual void channelClosedEventRecv(uint8_t) = 0;
			virtual void broadcastDataEventRecv(uint8_t) = 0;
			virtual void acknowledgedDataEventRecv(uint8_t) = 0;
			virtual void burstTransfertDataEventRecv(uint8_t) = 0;
			virtual void advancedBurstDataEventRecv(uint8_t) = 0;
			virtual void channelStatusEventRecv(uint8_t) = 0;
			virtual void channelIdEventRecv(uint8_t) = 0;
			virtual void requestedMessageEventRecv(uint8_t) = 0;

			virtual void channelStatusRecv(uint8_t);
			virtual void channelIdRecv(uint16_t, uint8_t, uint8_t);

			virtual int32_t broadcastDataRecv(uint8_t *msg, int32_t length);
			virtual int32_t acknowledgedDataRecv(uint8_t *msg, int32_t length);
			virtual int32_t burstTransfertDataRecv(uint8_t *msg, int32_t length);
			virtual int32_t advancedBurstDataRecv(uint8_t *msg, int32_t length);
			virtual int32_t extendedBroadcastDataRecv(uint8_t *msg, int32_t length);
			virtual int32_t extendedAcknowledgedDataRecv(uint8_t *msg, int32_t length);
			virtual int32_t extendedBurstDataRecv(uint8_t *msg, int32_t length);

		protected:
			virtual int32_t dataRecv(uint8_t *, int32_t);
		
			/*
			 * common pages
			 */
			virtual int32_t dataPageRequestRecv(uint8_t *, int32_t);
			virtual int32_t modesettingPageRecv(uint8_t *, int32_t);
			virtual int32_t multiComponentSystemManufacturerInformationRecv(uint8_t *, int32_t);
			virtual int32_t multiComponentSystemProductInformationRecv(uint8_t *, int32_t);
			virtual int32_t commonPage80Recv(uint8_t *, int32_t);
			virtual int32_t commonPage81Recv(uint8_t *, int32_t);
			virtual int32_t batteryStatusRecv(uint8_t *, int32_t);
			virtual int32_t timeDateRecv(uint8_t *, int32_t);
			virtual int32_t commonPage85Recv(uint8_t *, int32_t);
			virtual int32_t commonPage86Recv(uint8_t *, int32_t);
			virtual int32_t commonPage87Recv(uint8_t *, int32_t);
			virtual int32_t specialEventPageRecv(uint8_t, uint8_t *, int32_t) = 0;

		protected:
			uint8_t  _channel_number;
			uint8_t  _channel_type;
			uint8_t  _network_number;
			uint8_t  _extended_assignment;
			uint16_t _channel_period;
			uint8_t  _search_timeout;
			uint8_t  _rf_frequency;
			uint16_t _device_number;
			uint8_t  _device_type_id;
			uint8_t  _transmission_type;
			uint8_t  _tx_power;
			Ant * _ant;

			uint8_t  _sport_mode;
			uint8_t  _hw_revision;
			uint8_t  _sw_revision;
			uint32_t _serial_number;
			uint16_t _manufacturer_id;
			uint16_t _model_number;
			uint8_t  _channel_status;
			uint8_t  _battery_identifier;
			uint8_t  _component_identifier;
			uint32_t _cumulative_operatging_time;
			uint8_t  _fractional_battery_voltage;
			uint8_t  _coarse_battery_voltage_use;
			uint8_t  _battery_status;
			uint8_t  _resolution;
			uint8_t  Peripheral_Device_Index;
			uint8_t  Total_Number;
			uint8_t  Channel_State;
			uint32_t Peripheral_Device_id;
	};
}

#endif /* ANT_H */
