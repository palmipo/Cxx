#include "antctrl.h"
#include "ant.h"
#include <iostream>

ANT::Ctrl::Ctrl(uint8_t channel_id, ANT::Ant * serial)
: ANT::Master::Master(channel_id, serial)
{
	_channel_type = 0x10;
	_network_number = 1;
	_extended_assignment = 0;
	_channel_period = 8192;
	_search_timeout = 30;
	_rf_frequency = 57;
	_device_number = 1;
	_device_type_id = 16;
	_transmission_type = 0x05;
}

ANT::Ctrl::~Ctrl()
{}

void ANT::Ctrl::sendAudioUpdateData(uint8_t volume, uint16_t total_track_time, uint16_t current_track_time, uint8_t audio_capabilities, uint8_t state)
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x01;
	msg[1] = volume;
	msg[2] = total_track_time & 0x00FF;
	msg[3] = (total_track_time & 0xFF00) >> 8;
	msg[4] = current_track_time & 0x00FF;
	msg[5] = (current_track_time & 0xFF00) >> 8;
	msg[6] = audio_capabilities;
	msg[7] = state;
	_ant->broadcastData(_channel_id, msg, len);
}

void ANT::Ctrl::sendControlDeviceAvailability(uint8_t current_notifications, uint8_t device_capabilities)
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x02;
	msg[1] = current_notifications;
	msg[2] = 0x00;
	msg[3] = 0x00;
	msg[4] = 0x00;
	msg[5] = 0x00;
	msg[6] = 0x00;
	msg[7] = device_capabilities;
	_ant->broadcastData(_channel_id, msg, len);
}

void ANT::Ctrl::sendTextData(int8_t * text, int32_t length)
{
	uint8_t len = 8;
	uint8_t msg[8];
	int32_t i = 0;
	uint8_t subpage_number = 0;
	while (i < length)
	{
		msg[0] = 0x05;
		msg[1] = subpage_number;
		msg[2] = text[i]; ++i;
		msg[3] = text[i]; ++i;
		msg[4] = text[i]; ++i;
		msg[5] = text[i]; ++i;
		msg[6] = text[i]; ++i;
		msg[7] = text[i]; ++i;
		_ant->broadcastData(_channel_id, msg, len);
	}
}

void ANT::Ctrl::sendVideoUpdateData(uint8_t volume, uint16_t time_remaining, uint16_t time_progressed, uint8_t video_capabilities, uint8_t state)
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x07;
	msg[1] = volume;
	msg[2] = time_remaining & 0x00FF;
	msg[3] = (time_remaining & 0xFF00) >> 8;
	msg[4] = time_progressed & 0x00FF;
	msg[5] = (time_progressed & 0xFF00) >> 8;
	msg[6] = video_capabilities;
	msg[7] = state;
	_ant->broadcastData(_channel_id, msg, len);
}

void ANT::Ctrl::sendAvailableText(int8_t * text, int32_t length)
{
	uint8_t len = 8;
	uint8_t msg[8];
	int32_t i = 0;
	uint8_t subpage_number = 0;
	while (i < length)
	{
		msg[0] = 0x05;
		msg[1] = subpage_number;
		msg[2] = text[i]; ++i;
		msg[3] = text[i]; ++i;
		msg[4] = text[i]; ++i;
		msg[5] = text[i]; ++i;
		msg[6] = text[i]; ++i;
		msg[7] = text[i]; ++i;
		_ant->broadcastData(_channel_id, msg, len);
	}
}

void ANT::Ctrl::sendAudioVideoCommand(uint8_t volume, uint16_t time_remaining, uint16_t time_progressed, uint8_t video_capabilities, uint8_t state)
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x10;
	msg[1] = volume;
	msg[2] = time_remaining & 0x00FF;
	msg[3] = (time_remaining & 0xFF00) >> 8;
	msg[4] = time_progressed & 0x00FF;
	msg[5] = (time_progressed & 0xFF00) >> 8;
	msg[6] = video_capabilities;
	msg[7] = state;
	_ant->broadcastData(_channel_id, msg, len);
}

void ANT::Ctrl::rfEventCallback(uint8_t channel_number, uint8_t response_code, void * data)
{
	ANT::Ctrl * ctrl = (ANT::Ctrl *)data;
	if (channel_number == ctrl->_channel_id)
	{
		switch (response_code)
		{
			case 3:
				// prepareMessageSuivant();
				break;
		}
	}
}