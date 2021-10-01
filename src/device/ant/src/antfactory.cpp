#include "antfactory.h"
//~ #include "rs232.h"
#include "anttempe.h"
#include "anthr.h"
#include "antspeedcadence.h"
//~ #include "antctrl.h"
#include <iostream>

ANT::AntFactory::AntFactory(const std::string & device)
: ANT::Ant(device)
, _last_chanel_number(1)
{
	resetSystem();
}

ANT::AntFactory::~AntFactory()
{
	for(std::map<uint8_t, ANT::Profile *>::iterator it = _devices.begin(); it != _devices.end(); ++it)
	{
		closeChannel(it->first);

		delete it->second;
		it->second = 0;
	}
}

ANT::Tempe * ANT::AntFactory::addTempeMonitor()
{
	ANT::Tempe * tempe = new ANT::Tempe(_last_chanel_number, _network_number, this);
	_devices[_last_chanel_number] = tempe;

	++_last_chanel_number;
	
	return tempe;
}

ANT::HeartRate * ANT::AntFactory::addHRMonitor()
{
	ANT::HeartRate * hr = new ANT::HeartRate(_last_chanel_number, _network_number, this);
	_devices[_last_chanel_number] = hr;

	++_last_chanel_number;
	
	return hr;
}

ANT::SpeedCadence * ANT::AntFactory::addSpeedCadenceMonitor()
{
	ANT::SpeedCadence * sc = new ANT::SpeedCadence(_last_chanel_number, _network_number, this);
	_devices[_last_chanel_number] = sc;

	++_last_chanel_number;
	
	return sc;
}

//~ ANT::Ctrl * ANT::AntFactory::addVideoCtrlMaster()
//~ {
	//~ ANT::Ctrl * ctrl = new ANT::Ctrl(_last_chanel_number, _network_number, this);
	//~ _devices[_last_chanel_number] = ctrl;

	//~ ++_last_chanel_number;
	
	//~ return ctrl;
//~ }

ANT::Profile * ANT::AntFactory::get(uint8_t channel_number)
{
	std::map<uint8_t, ANT::Profile *>::iterator it = _devices.find(channel_number);
	if (it != _devices.end())
	{
		return it->second;
	}
	
	throw std::string("pas trouve");
}

void ANT::AntFactory::close(uint8_t channel_number)
{
	closeChannel(channel_number);
	
	std::map<uint8_t, ANT::Profile *>::iterator it = _devices.find(channel_number);
	if (it != _devices.end())
	{
		delete it->second;
		_devices.erase(it);
	}
}


int32_t ANT::AntFactory::broadcastDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t channel_number = msg[cpt]; cpt += 1;
	cpt += get(channel_number)->broadcastDataRecv(msg+cpt, length-cpt);
	return cpt;
}

int32_t ANT::AntFactory::acknowledgedDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t channel_number = msg[cpt]; cpt += 1;
	cpt += get(channel_number)->acknowledgedDataRecv(msg+cpt, length-cpt);
	return cpt;
}

int32_t ANT::AntFactory::burstTransfertDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t channel_number = msg[cpt]; cpt += 1;
	cpt += get(channel_number)->burstTransfertDataRecv(msg+cpt, length-cpt);
	return cpt;
}

int32_t ANT::AntFactory::advancedBurstDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t channel_number = msg[cpt]; cpt += 1;
	cpt += get(channel_number)->advancedBurstDataRecv(msg+cpt, length-cpt);
	return cpt;
}

int32_t ANT::AntFactory::extendedBroadcastDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t a;
	uint16_t b;
	uint8_t c;
	uint8_t d;
	uint8_t* e;
	return cpt;
}

int32_t ANT::AntFactory::extendedAcknowledgedDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t a;
	uint16_t b;
	uint8_t c;
	uint8_t d;
	uint8_t* e;
	return cpt;
}

int32_t ANT::AntFactory::extendedBurstDataRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t a;
	uint16_t b;
	uint8_t c;
	uint8_t d;
	uint8_t* e;
	return cpt;
}

int32_t ANT::AntFactory::startupMessageRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t startup_message = msg[cpt]; cpt += 1;
	uint8_t netkey[] = {0xB9, 0xA5, 0x21, 0xFB, 0xBD, 0x72, 0xC3, 0x45};
	setNetworkKey(_network_number, netkey);
	return cpt;
}

int32_t ANT::AntFactory::serialErrorMessageRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t error_number = msg[cpt]; ++cpt;
	return cpt;
}

int32_t ANT::AntFactory::channelStatusRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t channel_number = msg[cpt]; cpt += 1;
	uint8_t channel_status = msg[cpt]; cpt += 1;
	get(channel_number)->channelStatusRecv(channel_status);
	return cpt;
}

int32_t ANT::AntFactory::channelIdRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t channel_number = msg[cpt]; cpt += 1;
	uint16_t device_number = msg[cpt]; ++cpt;
	device_number |= (msg[cpt] << 8); ++cpt;
	uint8_t device_type_id = msg[cpt]; ++cpt;
	uint8_t transmission_type = msg[cpt]; ++cpt;
	get(channel_number)->channelIdRecv(device_number, device_type_id, transmission_type);
	return cpt;
}

int32_t ANT::AntFactory::antVersionRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	return 0;
}

int32_t ANT::AntFactory::capabilitiesRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t max_channel = msg[cpt]; cpt += 1;
	uint8_t max_network = msg[cpt]; cpt += 1;
	uint8_t standard_options = msg[cpt]; cpt += 1;
	uint8_t advanced_options = msg[cpt]; cpt += 1;
	uint8_t advanced_options_2 = msg[cpt]; cpt += 1;
	uint8_t advanced_options_3 = msg[cpt]; cpt += 1;
	uint8_t advanced_options_4 = msg[cpt]; cpt += 1;
	return cpt;
}

int32_t ANT::AntFactory::serialNumberRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint32_t serial_number = msg[cpt] << 24; cpt += 1;
	serial_number |= msg[cpt] << 16; cpt += 1;
	serial_number |= msg[cpt] << 8; cpt += 1;
	serial_number |= msg[cpt]; cpt += 1;
	return cpt;
}

int32_t ANT::AntFactory::eventBufferConfigurationRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	cpt += 1;
	uint8_t buffer_config = msg[cpt]; cpt += 1;
	uint16_t buffer_size = msg[cpt] << 8; cpt += 1;
	buffer_size |= msg[cpt]; cpt += 1;
	uint16_t buffer_time = msg[cpt] << 8; cpt += 1;
	buffer_time |= msg[cpt]; cpt += 1;
	return cpt;
}

int32_t ANT::AntFactory::advancedBurstCapabilitiesRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t supported_max_packed_length = msg[cpt]; cpt += 1;
	uint32_t supported_feature = msg[cpt] << 16; cpt += 1;
	supported_feature |= msg[cpt] << 8; cpt += 1;
	supported_feature |= msg[cpt]; cpt += 1;
	return cpt;
}

int32_t ANT::AntFactory::advancedBurstCurrentConfigurationRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t enable = msg[cpt]; cpt += 1;
	uint8_t max_packed_length = msg[cpt]; cpt += 1;
	uint32_t required_features = msg[cpt] << 16; cpt += 1;
	required_features |= msg[cpt] << 8; cpt += 1;
	required_features |= msg[cpt]; cpt += 1;
	uint32_t optional_features = msg[cpt] << 16; cpt += 1;
	optional_features |= msg[cpt] << 8; cpt += 1;
	optional_features |= msg[cpt]; cpt += 1;
	uint8_t optional_stall_count = msg[cpt]; cpt += 1;
	return cpt;
}

int32_t ANT::AntFactory::eventFilterRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	cpt += 1;
	uint16_t event_filter = msg[cpt] << 8; cpt += 1;
	event_filter |= msg[cpt]; cpt += 1;

	return cpt;
}

int32_t ANT::AntFactory::selectiveDataUpdateMaskSettingRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t sdu_mask_number = msg[cpt]; ++cpt;
	uint8_t sdu_mask[8];
	for (int32_t i=0; i<8; ++i)
		sdu_mask[i] = msg[cpt]; ++cpt;

	return cpt;
}

int32_t ANT::AntFactory::userNvmRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	cpt += 1;
	uint8_t data[512];
	for (int32_t i=0; msg[cpt]; ++i)
	{
		data[i] = msg[cpt];
		cpt += 1;
	}
	return cpt;
}

int32_t ANT::AntFactory::encryptionModeParametersRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	uint8_t a;
	uint8_t * b;
	return cpt;
}

int32_t ANT::AntFactory::channelMessagesRecv(uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;

	uint8_t channel_number = msg[cpt]; ++cpt;
	uint8_t Initiating_Message_ID = msg[cpt]; ++cpt;

	if (Initiating_Message_ID == 0x01)
	{
		uint8_t event_code = msg[cpt]; ++cpt;
		uint8_t optional_event_code_parameters = 0;
		if (cpt < length)
		{
			uint8_t optional_event_code_parameters = msg[cpt]; ++cpt;
		}

		get(channel_number)->channelEventRecv(event_code, optional_event_code_parameters);
	}
	else
	{
		uint8_t Response_Code = msg[cpt]; ++cpt;

		if (Initiating_Message_ID == 0x41)
		{
			get(channel_number)->unassignedChannelEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x42)
		{
			get(channel_number)->assignedChannelEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x43)
		{
			get(channel_number)->channelPeriodEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x44)
		{
			get(channel_number)->searchTimeoutEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x45)
		{
			get(channel_number)->channelRfFrequencyEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x46)
		{
			networkKeyRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x47)
		{
			transmitPowerEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x49)
		{
			get(channel_number)->searchWaveformEventRecv(Response_Code);
		}
		//~ else if (Initiating_Message_ID == 0x4A)
		//~ {
			// resetSystemRecv(Response_Code);
		//~ }
		else if (Initiating_Message_ID == 0x4B)
		{
			get(channel_number)->channelOpenedEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4C)
		{
			get(channel_number)->channelClosedEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4D)
		{
			get(channel_number)->requestedMessageEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4E)
		{
			get(channel_number)->broadcastDataEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4F)
		{
			get(channel_number)->acknowledgedDataEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4F)
		{
			get(channel_number)->burstTransfertDataEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4F)
		{
			get(channel_number)->advancedBurstDataEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x4F)
		{
			get(channel_number)->channelStatusEventRecv(Response_Code);
		}
		else if (Initiating_Message_ID == 0x51)
		{
			get(channel_number)->channelIdEventRecv(Response_Code);
		}
		else
		{
			std::cout << __FILE__ << " " << __LINE__ << " Initiating_Message_ID : " << (int)Initiating_Message_ID << " a faire !!!" << std::endl;
		}
	}

	return cpt;
}

void ANT::AntFactory::networkKeyRecv(uint8_t Response_Code)
{}

void ANT::AntFactory::transmitPowerEventRecv(uint8_t Response_Code)
{}
