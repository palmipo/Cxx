#include "antspeedcadence.h"

#include "ant.h"


#include <iostream>

ANT::SpeedCadence::SpeedCadence(uint8_t channel_id, uint8_t network_number, ANT::Ant * serial)
: ANT::Slave(channel_id, serial)
{
	_channel_type = 0;
	_network_number = network_number;
	_extended_assignment = 0;
	_channel_period = 8102;
	_search_timeout = 30;
	_rf_frequency = 57;
	_device_number = 0;
	_device_type_id = 122;
	_transmission_type = 0;
}

ANT::SpeedCadence::~SpeedCadence()
{}

int32_t ANT::SpeedCadence::specialEventPageRecv(uint8_t page_id, uint8_t *msg, int32_t length)
{
	int32_t cpt = 0;
	switch (page_id & 0x7F)
	{
		case 0:
/*
0 Bike Cadence Event Time LSB 2 Bytes Represents the time of the last valid bike cadence event 1/1024 second 64s
1 Bike Cadence Event Time MSB 2 Cumulative Cadence Revolution Count LSB
2 Bytes Represents the total number of pedal revolutions Events 65536
3 Cumulative Cadence Revolution Count MSB
*/
			cpt += 3;
			break;

		case 1:
/*
0 Data Page Number 7 Bits Data Page Number = 1 (0x01) N/A N/A
0 Page Change Toggle 1 Bit (MSB) The transmitter shall [MD_0005] toggle this bit every 4th message. Refer to section 5.2.4.1. N/A N/A
1 Cumulative Operating Time LSB 3 Bytes Increments every 2 seconds and is reset on battery replacement. 2 seconds 33554432s
2 Cumulative Operating Time
3 Cumulative Operating Time MSB
*/
			cpt += 3;
			break;

		default:
			cpt += 3;
			break;
	}

/*
4 Bike Speed Event Time LSB 2 Bytes Represents the time of the last valid bike speed event 1/1024 second 64s
5 Bike Speed Event Time MSB
6 Cumulative Speed Revolution Count LSB 2 Bytes Represents the total number of wheel revolutions Events 65536
7 Cumulative Speed Revolution Count MSB
*/
	uint16_t Cumulative_Cadence_Revolution_Count = msg[cpt]; ++cpt;
	Cumulative_Cadence_Revolution_Count |= (msg[cpt] << 8); ++cpt;

	uint16_t Bike_Cadence_Event_Time = msg[cpt]; ++cpt;
	Bike_Cadence_Event_Time |= (msg[cpt] << 8); ++cpt;

	return cpt;
}

