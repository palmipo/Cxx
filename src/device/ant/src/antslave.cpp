#include "antslave.h"
#include "ant.h"
#include <iostream>

ANT::Slave::Slave(uint8_t channel_id, ANT::Ant * protocol)
: ANT::Profile(channel_id, protocol)
{}

ANT::Slave::~Slave()
{}

void ANT::Slave::init()
{
	_ant->assignChannel(_channel_number, _channel_type, _network_number, 0);
}

void ANT::Slave::unassignedChannelEventRecv(uint8_t)
{}

void ANT::Slave::assignedChannelEventRecv(uint8_t)
{
	_ant->channelId(_channel_number, _device_number, _device_type_id, _transmission_type);
}

void ANT::Slave::channelPeriodEventRecv(uint8_t)
{
	_ant->openChannel(_channel_number);
}

void ANT::Slave::searchTimeoutEventRecv(uint8_t)
{}

void ANT::Slave::channelRfFrequencyEventRecv(uint8_t)
{
	_ant->channelPeriod(_channel_number, _channel_period);
}

void ANT::Slave::searchWaveformEventRecv(uint8_t)
{}

void ANT::Slave::channelOpenedEventRecv(uint8_t)
{}

void ANT::Slave::channelClosedEventRecv(uint8_t)
{
	_ant->unassignChannel(_channel_number);
}

void ANT::Slave::channelIdEventRecv(uint8_t)
{
	_ant->channelRfFrequency(_channel_number, _rf_frequency);
}

void ANT::Slave::channelStatusEventRecv(uint8_t channel_status)
{}

void ANT::Slave::requestedMessageEventRecv(uint8_t)
{}

void ANT::Slave::broadcastDataEventRecv(uint8_t)
{}

void ANT::Slave::acknowledgedDataEventRecv(uint8_t)
{}

void ANT::Slave::burstTransfertDataEventRecv(uint8_t)
{}

void ANT::Slave::advancedBurstDataEventRecv(uint8_t)
{}
