#include "ant.h"
#include "rs232.h"
#include <iostream>
#include <iomanip>

ANT::Ant::Ant(const std::string & device_p)
: PollFactory()
, _handler(-1)
{
    RS232 * serial = new RS232(device_p);
    if (serial)
    {
		serial->setConfig(B57600, 8, 'N', 1);
		serial->setInterCharacterTimer(1);
        _handler = serial->handler();
		add(serial);
    }
}

ANT::Ant::~Ant()
{
	del(_handler);
}

void ANT::Ant::unassignChannel(uint8_t channel_number)
{
	send(0x41, &channel_number, 1);
}

void ANT::Ant::assignChannel(uint8_t channel_number, uint8_t channel_type, uint8_t network_number, uint8_t extended_assignement)
{
	uint8_t msg[3];
	msg[0] = channel_number;
	msg[1] = channel_type;
	msg[2] = network_number;
	send(0x42, msg, 3);
}
 
void ANT::Ant::channelId(uint8_t channel_number, uint16_t device_number, uint8_t device_type_id, uint8_t trans_type)
{
	uint8_t cpt = 0;
	uint8_t msg[5];
	
	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = device_number & 0xFF; ++cpt;
	msg[cpt] = (device_number & 0xFF00) >> 8; ++cpt;
	msg[cpt] = device_type_id; ++cpt;
	msg[cpt] = trans_type; ++cpt;
	
	send(0x51, msg, cpt);
}

void ANT::Ant::channelPeriod(uint8_t channel_number, uint16_t channel_period)
{
	uint8_t msg[3];
	msg[0] = channel_number;
	msg[1] = channel_period & 0xFF;
	msg[2] = (channel_period & 0xFF00) >> 8;
	send(0x43, msg, 3);
}

void ANT::Ant::searchTimeout(uint8_t channel_number, uint8_t search_timeout)
{
	uint8_t msg[3];
	msg[0] = channel_number;
	msg[1] = search_timeout;
	send(0x44, msg, 2);
}

void ANT::Ant::channelRfFrequency(uint8_t channel_number, uint8_t rf_frequency)
{
	uint8_t msg[3];
	msg[0] = channel_number;
	msg[1] = rf_frequency;
	send(0x45, msg, 2);
}

/* B9:A5:21:FB:BD:72:C3:45 */
void ANT::Ant::setNetworkKey(uint8_t network_number, uint8_t *network_key)
{
	uint8_t cpt = 0;
	uint8_t msg[255];
	msg[cpt++] = network_number;
	for (uint8_t i=0; i<8; ++i)
		msg[cpt++] = network_key[i];
	send(0x46, msg, cpt);
}

void ANT::Ant::transmitPower(uint8_t tx_power)
{
	uint8_t cpt = 0;
	uint8_t msg[255];
	msg[cpt++] = 0;
	msg[cpt++] = tx_power;
	send(0x47, msg, cpt);
}

void ANT::Ant::searchWaveForm(uint8_t channel_number, uint16_t wave_form)
{
	uint8_t cpt = 0;
	uint8_t msg[255];
	msg[cpt++] = channel_number;
	msg[cpt++] = wave_form & 0xFF;
	msg[cpt++] = (wave_form & 0xFF00) << 8;
	send(0x49, msg, cpt);
}

void ANT::Ant::addChannelIdToList(uint8_t channel_number, uint8_t device_number, uint8_t device_type_id, uint8_t trans_type, uint8_t list_index)
{
	uint8_t cpt = 0;
	uint8_t msg[255];
	msg[cpt] = channel_number; cpt += 1;
	msg[cpt] = device_number; cpt += 1;
	msg[cpt] = device_type_id; cpt += 1;
	msg[cpt] = trans_type; cpt += 1;
	msg[cpt] = list_index; cpt += 1;
	send(0x59, msg, cpt);
}

void ANT::Ant::addEncryptionIdToList(uint8_t channel_number, uint8_t encryption_id, uint8_t list_index)
{
	uint8_t cpt = 0;
	uint8_t msg[255];
	send(0x59, msg, cpt);
}

void ANT::Ant::configEncryptionIdList(uint8_t channel_number, uint8_t list_size, uint8_t list_type)
{
	uint8_t cpt = 0;
	uint8_t msg[255];
	send(0x5A, msg, cpt);
}

void ANT::Ant::setChannelTransmitPower(uint8_t channel_number, uint8_t transmit_power)
{
	uint8_t cpt = 0;
	uint8_t msg[100];
	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = transmit_power; ++cpt;
	send(0x60, msg, cpt);
}

void ANT::Ant::lowPrioritySearchTimeout(uint8_t channel_number, uint8_t search_timeout)
{
	uint8_t cpt = 0;
	uint8_t msg[100];
	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = search_timeout; ++cpt;
	send(0x63, msg, cpt);
}

void ANT::Ant::serialNumberSetChannelID(uint8_t channel_number, uint8_t Device_Type_ID, uint8_t Trans_Type)
{
	uint8_t cpt = 0;
	uint8_t msg[100];
	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = Device_Type_ID; ++cpt;
	msg[cpt] = Trans_Type; ++cpt;
	send(0x65, msg, cpt);
}

void ANT::Ant::enableExtRXMessages(uint8_t enable)
{
	uint8_t msg = 0;
	send(0x66, &msg, 1);
}

void ANT::Ant::enableLED(uint8_t enable)
{
	uint8_t msg = 0;
	send(0x68, &msg, 1);
}

void ANT::Ant::crystalEnable()
{
	uint8_t msg = 0;
	send(0x6D, &msg, 1);
}

void ANT::Ant::libConfig(uint8_t lib_config)
{
	uint8_t msg = 0;
	send(0x6E, &msg, 1);
}

void ANT::Ant::frequencyAgility(uint8_t channel_number, uint8_t freq1, uint8_t freq2, uint8_t freq3)
{
	uint8_t msg = 0;
	send(0x70, &msg, 1);
}

void ANT::Ant::proximitySearch(uint8_t channel_number, uint8_t search_threashold)
{
	uint8_t msg = 0;
	send(0x71, &msg, 1);
}

void ANT::Ant::configureEventBuffer(uint8_t config, uint16_t size, uint16_t time)
{
	int32_t cpt = 0;
	uint8_t msg[512];
	msg[0] = config; cpt += 1;
	msg[0] = size >> 8; cpt += 1;
	msg[0] = size & 0xFF; cpt += 1;
	msg[0] = time >> 8; cpt += 1;
	msg[0] = time & 0xFF; cpt += 1;
	send(0x74, msg, cpt);
}

void ANT::Ant::channelSearchPriority(uint8_t channel_number, uint8_t search_priority)
{
	uint8_t msg = 0;
	send(0x75, &msg, 1);
}

void ANT::Ant::set128BitNetworkKey(uint8_t channel_number, uint8_t * network_key)
{
	uint8_t msg = 0;
	send(0x76, &msg, 1);
}

void ANT::Ant::highDutySearch(uint8_t enable, uint16_t suppression_cycle)
{
	uint8_t msg = 0;
	send(0x77, &msg, 1);
}

void ANT::Ant::configureAdvancedBurst(uint8_t enable, uint8_t max_packet_length, uint32_t required_features, uint32_t optional_features, uint8_t optional_stall_count)
{

	uint8_t msg = 0;
	send(0x78, &msg, 1);
}

void ANT::Ant::configureEventFilter(uint16_t event_filter)
{
	uint8_t msg = 0;
	send(0x79, &msg, 1);
}

void ANT::Ant::configureSelectiveDataUpdates(uint8_t channel_number, uint8_t selected_data)
{
	uint8_t msg = 0;
	send(0x7A, &msg, 1);
}

void ANT::Ant::setSelectiveDataUpdateMask(uint8_t sdu_mask_number, uint8_t * sdu_mask)
{
	uint8_t msg = 0;
	send(0x7B, &msg, 1);
}

void ANT::Ant::configureUserNvm(uint16_t address, uint8_t * data, int32_t length)
{
	uint8_t msg = 0;
	send(0x7C, &msg, 1);
}

void ANT::Ant::enableSingleChannelEncryption(uint8_t channel_number, uint8_t encryption_mode, uint8_t volatile_key_index, uint8_t decimation_rate)
{
	uint8_t msg = 0;
	send(0x7D, &msg, 1);
}

void ANT::Ant::setEncryptionKey(uint8_t volatile_key_index, uint8_t * encryption_key)
{
	uint8_t msg = 0;
	send(0x7E, &msg, 1);
}

void ANT::Ant::setEncryptionInfo(uint8_t set_parameter, uint8_t * data_string)
{
	uint8_t msg = 0;
	send(0x7F, &msg, 1);
}

void ANT::Ant::channelSearchSharing(uint8_t channel_number, uint8_t sharing_cycles)
{
	uint8_t msg = 0;
	send(0x81, &msg, 1);
}

void ANT::Ant::loadStoreEncryptionKey(uint8_t operation, uint8_t nvm_key_index, uint8_t * volatile_key_index_or_encryption_key)
{
	uint8_t msg = 0;
	send(0x83, &msg, 1);
}

void ANT::Ant::setUsbDescriptorString(uint8_t descriptor_string_numbern, uint8_t * descriptor_stringn, uint8_t string_length)
{
	uint8_t msg = 0;
	send(0xC7, &msg, 1);
}

void ANT::Ant::resetSystem()
{
	uint8_t msg = 0;
	send(0x4A, &msg, 1);
}

void ANT::Ant::openChannel(uint8_t channel_number)
{
	send(0x4B, &channel_number, 1);
}

void ANT::Ant::closeChannel(uint8_t channel_number)
{
	send(0x4C, &channel_number, 1);
}

void ANT::Ant::requestMessage(uint8_t channel_number, uint8_t request_message_id, uint8_t * request_message, uint8_t request_message_length)
{
	uint8_t cpt = 0;
	uint8_t msg[512];

	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = request_message_id; ++cpt;

	for (uint8_t i=0; i<request_message_length; ++i)
	{
		msg[cpt] = request_message[i]; ++cpt;
	}
	
	send(0x4D, msg, cpt);
}

void ANT::Ant::openRxScanMode(uint8_t *, uint16_t synchronousChannelPacketsOnly)
{
	uint8_t cpt = 0;
	uint8_t msg[100];
	msg[cpt] = 0; ++cpt;
	msg[cpt] = synchronousChannelPacketsOnly & 0xFF; ++cpt;
	msg[cpt] = (synchronousChannelPacketsOnly & 0xFF00) >> 8; ++cpt;
	send(0x5B, msg, cpt);
}

void ANT::Ant::sleepMessage()
{
	uint8_t msg = 0;
	send(0xC5, &msg, 1);
}

void ANT::Ant::broadcastData(uint8_t channel_number, uint8_t * request_message, uint16_t request_message_length)
{
	uint8_t cpt = 0;
	uint8_t msg[1 + request_message_length];

	msg[cpt] = channel_number; ++cpt;
	
	for (uint8_t i=0; i<request_message_length; ++i)
	{
		msg[cpt] = request_message[i]; ++cpt;
	}
	
	send(0x4E, msg, cpt);
}

void ANT::Ant::acknowledgedData(uint8_t channel_number, uint8_t * request_message, uint16_t request_message_length)
{
	uint8_t cpt = 0;
	uint8_t msg[1 + request_message_length];

	msg[cpt] = channel_number; ++cpt;
	
	for (uint8_t i=0; i<request_message_length; ++i)
	{
		msg[cpt] = request_message[i]; ++cpt;
	}
	
	send(0x4F, msg, cpt);
}

void ANT::Ant::burstTransferData(uint8_t channel_number, uint8_t * request_message, uint16_t request_message_length)
{
	uint8_t cpt = 0;
	uint8_t msg[1 + request_message_length];

	msg[cpt] = channel_number; ++cpt;
	
	for (uint8_t i=0; i<request_message_length; ++i)
	{
		msg[cpt] = request_message[i]; ++cpt;
	}
	
	send(0x50, msg, cpt);
}

void ANT::Ant::advancedBurstData(uint8_t channel_number, uint8_t * request_message, uint8_t request_message_length)
{
	uint8_t cpt = 0;
	uint8_t msg[1 + request_message_length];

	msg[cpt] = channel_number; ++cpt;
	
	for (uint8_t i=0; i<request_message_length; ++i)
	{
		msg[cpt] = request_message[i]; ++cpt;
	}
	
	send(0x72, msg, cpt);
}

void ANT::Ant::cwInit()
{
	uint8_t msg = 0;
	send(0x53, &msg, 1);
}

void ANT::Ant::cwTest(uint8_t tx_power, uint8_t rf_freq)
{
	uint8_t cpt = 0;
	uint8_t msg[3];

	msg[cpt] = 0; cpt += 1;
	msg[cpt] = tx_power; cpt += 1;
	msg[cpt] = rf_freq; cpt += 1;

	send(0x48, msg, cpt);
}

void ANT::Ant::extendedBroadcastData(uint8_t channel_number, uint16_t device_number, uint8_t device_type_id, uint8_t trans_type, uint8_t * payload)
{
	uint8_t cpt = 0;
	uint8_t msg[512];

	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = device_number >> 8; ++cpt;
	msg[cpt] = device_number & 0xFF; ++cpt;
	msg[cpt] = device_type_id; ++cpt;
	msg[cpt] = trans_type; ++cpt;
	
	for (uint8_t i=0; i<8; ++i)
	{
		msg[cpt] = payload[i]; ++cpt;
	}
	
	send(0x5D, msg, cpt);
}

void ANT::Ant::extendedAcknowledgedData(uint8_t channel_number, uint16_t device_number, uint8_t device_type_id, uint8_t trans_type, uint8_t * payload)
{
	uint8_t cpt = 0;
	uint8_t msg[512];

	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = device_number >> 8; ++cpt;
	msg[cpt] = device_number & 0xFF; ++cpt;
	msg[cpt] = device_type_id; ++cpt;
	msg[cpt] = trans_type; ++cpt;
	
	for (uint8_t i=0; i<8; ++i)
	{
		msg[cpt] = payload[i]; ++cpt;
	}
	
	send(0x5E, msg, cpt);
}

void ANT::Ant::extendedBurstData(uint8_t channel_number, uint16_t device_number, uint8_t device_type_id, uint8_t trans_type, uint8_t * payload)
{
	uint8_t cpt = 0;
	uint8_t msg[512];

	msg[cpt] = channel_number; ++cpt;
	msg[cpt] = device_number >> 8; ++cpt;
	msg[cpt] = device_number & 0xFF; ++cpt;
	msg[cpt] = device_type_id; ++cpt;
	msg[cpt] = trans_type; ++cpt;
	
	for (uint8_t i=0; i<8; ++i)
	{
		msg[cpt] = payload[i]; ++cpt;
	}
	
	send(0x5F, msg, cpt);
}

int32_t ANT::Ant::send ( uint8_t msg_id, uint8_t *msg, int32_t length )
{
	int32_t cpt = 0;
	uint8_t buffer[512];

	buffer[cpt] = 0xA4; ++cpt;
	buffer[cpt] = length; ++cpt;
	buffer[cpt] = msg_id; ++cpt;

	for (uint8_t i=0; i<length; ++i)
	{
		buffer[cpt] = msg[i]; ++cpt;
	}

	buffer[cpt] = checksum(buffer, cpt); ++cpt;
	buffer[cpt] = 0; ++cpt;
	buffer[cpt] = 0; ++cpt;

	int32_t nb = ((RS232*)get(_handler))->write(buffer, cpt);
	
	scrute(100);

	return nb;
}


uint8_t ANT::Ant::checksum(uint8_t *msg, uint8_t length)
{
	uint8_t sum = 0;
	for (int i=0; i<length; ++i)
	{
		sum ^= msg[i];
	}

	return sum;
}

int32_t ANT::Ant::actionIn(PollDevice * device)
{
	uint8_t data[512];
	uint16_t nb, nb_data = 0;
	do
	{
		nb = ((RS232*)device)->read(data+nb_data, 512-nb_data);
		nb_data += nb;
	}
	while (nb);

	recv(data, nb_data);
	
	return nb;
}


int32_t ANT::Ant::actionOut(PollDevice * device)
{
	return device->actionOut();
}


int32_t ANT::Ant::actionError(PollDevice * device)
{
	return device->actionError();
}


int32_t ANT::Ant::recv(const uint8_t * msg, int32_t length)
{
	int32_t cpt = 0;
	while (cpt < length)
	{
		uint8_t magic_number = msg[cpt]; ++cpt;
		if (magic_number != 0xA4)
		{
			return -1;
		}

		uint8_t len = msg[cpt]; ++cpt;
		if (length < 4 + len)
		{
			return -1;
		}

		uint8_t id = msg[cpt]; ++cpt;
		uint8_t msg_id = id & 0x7F;

		// ANT version
		if (msg_id == 0x3E)
		{
			uint8_t * msg;
			int32_t length;
			antVersionRecv(msg, len);
		}

		// Channel Messsage
		else if (msg_id == 0x40)
		{
			cpt += channelMessagesRecv((uint8_t*)(msg+cpt), len);
		}

		// broadcast data
		else if (msg_id == 0x4E)
		{
			cpt += broadcastDataRecv((uint8_t*)(msg+cpt), len);
		}

		// Acknowledged data
		else if (msg_id == 0x4F)
		{
			cpt += acknowledgedDataRecv((uint8_t*)(msg+cpt), len);
		}

		// Burst Transfer Data
		else if (msg_id == 0x50)
		{
			cpt += burstTransfertDataRecv((uint8_t*)(msg+cpt), len);
		}

		// Channel ID
		else if (msg_id == 0x51)
		{
			uint8_t channel_number = msg[cpt]; cpt += 1;
			uint16_t device_number = msg[cpt]; ++cpt;
			device_number |= (msg[cpt] << 8); ++cpt;
			uint8_t device_type_id = msg[cpt]; ++cpt;
			uint8_t transmission_type = msg[cpt]; ++cpt;
			channelIdRecv(channel_number, device_number, device_type_id, transmission_type);
		}

		// Channel Status
		else if (msg_id == 0x52)
		{
			uint8_t channel_number = msg[cpt]; cpt += 1;
			uint8_t channel_status = msg[cpt]; cpt += 1;
			channelStatusRecv(channel_number, channel_status);
		}

		// Capabilities
		else if (msg_id == 0x54)
		{
			uint8_t max_channel = msg[cpt]; cpt += 1;
			uint8_t max_network = msg[cpt]; cpt += 1;
			uint8_t standard_options = msg[cpt]; cpt += 1;
			uint8_t advanced_options = msg[cpt]; cpt += 1;
			uint8_t advanced_options_2 = msg[cpt]; cpt += 1;
			uint8_t advanced_options_3 = msg[cpt]; cpt += 1;
			uint8_t advanced_options_4 = msg[cpt]; cpt += 1;
			capabilitiesRecv(max_channel , max_network, standard_options, advanced_options, advanced_options_2, advanced_options_3, advanced_options_4);
		}

		// Extended Broadcast Data
		else if (msg_id == 0x5D)
		{
			uint8_t a;
			uint16_t b;
			uint8_t c;
			uint8_t d;
			uint8_t* e;
			extendedBroadcastDataRecv(a, b, c, d, e);
		}

		// Extended Acknowledged Data
		else if (msg_id == 0x5E)
		{
			uint8_t a;
			uint16_t b;
			uint8_t c;
			uint8_t d;
			uint8_t* e;
			extendedAcknowledgedDataRecv(a, b, c, d, e);
		}

		// Extended Burst Data
		else if (msg_id == 0x5F)
		{
			uint8_t a;
			uint16_t b;
			uint8_t c;
			uint8_t d;
			uint8_t* e;
			extendedBurstDataRecv(a, b, c, d, e);
		}

		// Serial Number
		else if (msg_id == 0x61)
		{
			uint32_t serial_number = msg[cpt] << 24; cpt += 1;
			serial_number |= msg[cpt] << 16; cpt += 1;
			serial_number |= msg[cpt] << 8; cpt += 1;
			serial_number |= msg[cpt]; cpt += 1;
			serialNumberRecv(serial_number);
		}

		// startup message
		else if (msg_id == 0x6F)
		{
			uint8_t startup_message = msg[cpt]; cpt += 1;
			startupMessageRecv(startup_message);
		}

		// Advanced Burst Data
		else if (msg_id == 0x72)
		{
			cpt += advancedBurstDataRecv((uint8_t*)(msg+cpt), len);
		}

		// Event Buffer Configuration
		else if (msg_id == 0x74)
		{
			cpt += 1;
			uint8_t buffer_config = msg[cpt]; cpt += 1;
			uint16_t buffer_size = msg[cpt] << 8; cpt += 1;
			buffer_size |= msg[cpt]; cpt += 1;
			uint16_t buffer_time = msg[cpt] << 8; cpt += 1;
			buffer_time |= msg[cpt]; cpt += 1;
			eventBufferConfigurationRecv(buffer_config, buffer_size, buffer_time);
		}

		// Advanced Burst
		else if (msg_id == 0x78)
		{
			uint8_t switch_id = msg[cpt]; ++cpt;
			if (switch_id == 0)
			{
				uint8_t supported_max_packed_length = msg[cpt]; cpt += 1;
				uint32_t supported_feature = msg[cpt] << 16; cpt += 1;
				supported_feature |= msg[cpt] << 8; cpt += 1;
				supported_feature |= msg[cpt]; cpt += 1;
				advancedBurstCapabilitiesRecv(supported_max_packed_length, supported_feature);
			}
			else
			{
				uint8_t enable = msg[cpt]; cpt += 1;
				uint8_t max_packed_length = msg[cpt]; cpt += 1;
				uint32_t required_features = msg[cpt] << 16; cpt += 1;
				required_features |= msg[cpt] << 8; cpt += 1;
				required_features |= msg[cpt]; cpt += 1;
				uint32_t optional_features = msg[cpt] << 16; cpt += 1;
				optional_features |= msg[cpt] << 8; cpt += 1;
				optional_features |= msg[cpt]; cpt += 1;
				uint8_t optional_stall_count = msg[cpt]; cpt += 1;
				advancedBurstCurrentConfigurationRecv(enable, max_packed_length, required_features, optional_features, optional_stall_count);
			}
		}

		// Event Filter
		else if (msg_id == 0x79)
		{
			cpt += 1;
			uint16_t event_filter = msg[cpt] << 8; cpt += 1;
			event_filter |= msg[cpt]; cpt += 1;
			eventFilterRecv(event_filter);
		}

		// Selective Data Update Mask Setting
		else if (msg_id == 0x7B)
		{
			uint8_t sdu_mask_number = msg[cpt]; ++cpt;
			uint8_t sdu_mask[8];
			for (int32_t i=0; i<8; ++i)
				sdu_mask[i] = msg[cpt]; ++cpt;
			selectiveDataUpdateMaskSettingRecv(sdu_mask_number, sdu_mask);
		}

		// User NVM
		else if (msg_id == 0x7C)
		{
			cpt += 1;
			uint8_t data[512];
			for (int32_t i=0; msg[cpt]; ++i)
			{
				data[i] = msg[cpt];
				cpt += 1;
			}
			userNvmRecv(data);
		}

		// Encryption Mode Parameters
		else if (msg_id == 0x7D)
		{
			uint8_t a;
			uint8_t * b;
			encryptionModeParametersRecv(a, b);
		}

		// error number
		else if (msg_id == 0xAE)
		{
			uint8_t error_number = msg[cpt]; ++cpt;
			serialErrorMessageRecv(error_number);
		}

		else
		{
		}

		uint8_t chksum = msg[cpt]; ++cpt;
	}
}
