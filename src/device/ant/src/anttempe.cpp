#include "anttempe.h"
#include "ant.h"
#include <iostream>

ANT::Tempe::Tempe(uint8_t channel_id, uint8_t network_key, ANT::Ant * protocol)
: ANT::Slave(channel_id, protocol)
{
	_channel_type = 0;
	_network_number = network_key;
	_extended_assignment = 0;
	_channel_period = 8192;
	_search_timeout = 45;
	_rf_frequency = 57;
	_device_number = 0;
	_device_type_id = 25;
	_transmission_type = 0;
}

ANT::Tempe::~Tempe()
{}

int32_t ANT::Tempe::specialEventPageRecv(uint8_t page_id, uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	switch (page_id & 0x7F)
	{
		case 0:
		{
			++cpt; // reserved
			++cpt; // reserved
			Transmission_Info = msg[cpt]; ++cpt;
			Supported_Pages = msg[cpt]; ++cpt;
			Supported_Pages |= (msg[cpt] << 8); ++cpt;
			Supported_Pages |= (msg[cpt] << 16); ++cpt;
			Supported_Pages |= (msg[cpt] << 24); ++cpt;

			uint8_t local_time = (Transmission_Info & 0x30) >> 4;
			uint8_t utc_time = (Transmission_Info & 0x0C) >> 2;
			uint8_t default_transmission_rate = (Transmission_Info & 0x03);
		} break;

		case 1:
			++cpt; // reserved

			event_count = msg[cpt]; ++cpt;
			
			lowest_temperature = msg[cpt]; ++cpt;
			lowest_temperature |= (msg[cpt] & 0xF0) << 4;

			highest_temperature = (msg[cpt] & 0x0F); ++cpt;
			highest_temperature |= msg[cpt] << 4; ++cpt;

			current_temperature = msg[cpt]; ++cpt;
			current_temperature |= msg[cpt] << 8; ++cpt;
			break;

		default:
			cpt += 7;
			break;
	}

	return cpt;
}
