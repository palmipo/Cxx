#include "antmaster.h"
#include "ant.h"
#include <iostream>

ANT::Master::Master(uint8_t channel_id, ANT::Ant * protocol)
: ANT::Profile::Profile(channel_id, protocol)
{}

ANT::Master::~Master()
{
	_ant->closeChannel(_channel_id);
}

void ANT::Master::init()
{
	_ant->setRfEventCallback(_channel_id, ANT::Master::rfEventCallback, this);
	_ant->setChannelUnassignedCallback(ANT::Master::channelUnassignedCallback, this);
	_ant->setChannelAssignedCallback(ANT::Master::channelAssignedCallback, this);
	_ant->setChannelPeriodCallback(ANT::Master::channelPeriodCallback, this);
	_ant->setSearchTimeoutCallback(ANT::Master::searchTimeoutCallback, this);
	_ant->setChannelRfFrequencyCallback(ANT::Master::channelRfFrequencyCallback, this);
	// _ant->setNetworkKeyCallback(ANT::Master::networkKeyCallback, this);
	_ant->setTransmitPowerCallback(ANT::Master::transmitPowerCallback, this);
	_ant->setSearchWaveformCallback(ANT::Master::searchWaveformCallback, this);
	// _ant->setResetSystemCallback(ANT::Master::resetSystemCallback, this);
	_ant->setChannelOpenedCallback(ANT::Master::channelOpenedCallback, this);
	_ant->setChannelClosedCallback(ANT::Master::channelClosedCallback, this);
	_ant->setChannelIdResponseCallback(ANT::Master::channelIdResponseCallback, this);
	_ant->setBroadcastDataCallback(ANT::Master::broadcastDataCallback, this);
	_ant->setAcknowledgedDataCallback(ANT::Master::acknowledgedDataCallback, this);
	_ant->setBurstTransfertDataCallback(ANT::Master::burstTransfertDataCallback, this);
	_ant->setChannelIdCallback(ANT::Master::channelIdCallback, this);
	_ant->setChannelStatusCallback(ANT::Master::channelStatusCallback, this);
	_ant->setAdvancedBurstDataCallback(ANT::Master::advancedBurstDataCallback, this);

	_ant->assignChannel(_channel_id, _channel_type, _network_number);
}

void ANT::Master::transmitPowerCallback(uint8_t response_code, void * data)
{
	// std::cout << __FILE__ << " " << __LINE__ << std::endl;
	ANT::Master * profile = (ANT::Master *)data;
	ANT::Ant * ant = profile->_ant;

	ant->openChannel(profile->_channel_id);
}
