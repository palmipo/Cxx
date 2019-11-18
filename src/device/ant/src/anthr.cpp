#include "anthr.h"

#include "ant.h"
#include <iostream>
#include <iomanip>

ANT::HeartRate::HeartRate(uint8_t channel_id, uint8_t network_key, ANT::Ant * serial)
: ANT::Slave(channel_id, serial)
, Features_Supported(0)
, Features_Enabled(0)
{
	_channel_type = 0;
	_network_number = network_key;
	_extended_assignment = 0;
	_channel_period = 8070;
	_search_timeout = 30;
	_rf_frequency = 57;
	_device_number = 0;
	_device_type_id = 120;
	_transmission_type = 0;
}

ANT::HeartRate::~HeartRate()
{}

void ANT::HeartRate::setSportMode(ANT::HeartRate::eSportMode mode)
{
	if (Features_Supported & (uint8_t)mode)
		modeSettingsPage((uint8_t)mode);
}

int32_t ANT::HeartRate::specialEventPageRecv(uint8_t page_id, uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	switch (page_id & 0x7F)
	{
		case 1:
			Cumulative_Operating_Time = msg[cpt]; ++cpt;
			Cumulative_Operating_Time |= msg[cpt] << 8; ++cpt;
			Cumulative_Operating_Time |= msg[cpt] << 16; ++cpt;
			break;
		
		case 2:
			Manufacturer_ID = msg[cpt]; ++cpt;
			Serial_Number = msg[cpt]; ++cpt;
			Serial_Number |= msg[cpt] << 8; ++cpt;
			break;
		
		case 3:
			Hardware_Version = msg[cpt]; ++cpt;
			Software_Version = msg[cpt]; ++cpt;
			Model_Number = msg[cpt]; ++cpt;
			break;
		
		case 4:
			Manufacturer_Specific = msg[cpt]; ++cpt;
			Previous_Heart_Beat_Event_Time = msg[cpt]; ++cpt;
			Previous_Heart_Beat_Event_Time |= msg[cpt] << 8; ++cpt;
			break;
		
		case 5:
			Interval_Average_Heart_Rate = msg[cpt]; ++cpt;
			Interval_Maximum_Heart_Rate = msg[cpt]; ++cpt;
			Session_Average_Heart_Rate = msg[cpt]; ++cpt;
			break;
		
		case 6:
			/*
			0xFF
			*/
			++cpt;

			/*
			Bit 0: Extended Running Features Supported
			Bit 1: Extended Cycling Features Supported
			Bit 2: Extended Swimming Features
			Supported
			Bits 3 – 5: Reserved. Set to 0
			Bits 6 – 7: Manufacturer-Specific Features
			*/
			Features_Supported = msg[cpt]; ++cpt;

			
			/*
			Bit 0: Extended Running Features Enabled
			Bit 1: Extended Cycling Features Enabled
			Bit 2: Extended Swimming Features Enabled
			Bits 3 – 5: Reserved. Set to 0
			Bits 6 – 7: Manufacturer-Specific Features
			*/
			Features_Enabled = msg[cpt]; ++cpt;
			break;
		
		case 7:
			/*
			Battery Level Percentage
			Reserved Values: 0x65 – 0xFE
			Set to 0xFF if not used.
			*/
			Battery_Level = msg[cpt]; ++cpt;

			/*
			1/256(V)
			*/
			Fractional_Battery_Voltage = msg[cpt]; ++cpt;
			
			/*
			bits 0 a 3 :
			0 a 14 Volts
			0xF (15): Invalid
			Coarse Battery Voltage
			
			bits 4 a 6 :
			0 (0x00) Reserved for future use
			1 (0x01) Battery Status = New
			2 (0x02) Battery Status = Good
			3 (0x03) Battery Status = OK
			4 (0x04) Battery Status = Low
			5 (0x05) Battery Status = Critical
			6 (0x06) Reserved for future use
			7 (0x07) Invalid
			
			bit 7 :
			Reserved (0x00) Receiver will not interpret this value at this time.
			*/
			Descriptive_Bit_Field = msg[cpt]; ++cpt;
			break;

		default:
			cpt += 3;
	}

	Heart_Beat_Event_Time = msg[cpt]; ++cpt;
	Heart_Beat_Event_Time |= msg[cpt] << 8; ++cpt;
	Heart_Beat_Count = msg[cpt]; ++cpt;
	Computed_Heart_Rate = msg[cpt]; ++cpt;
	
	return cpt;
}
