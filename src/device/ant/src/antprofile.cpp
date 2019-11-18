#include "antprofile.h"
#include "ant.h"
#include <iostream>

ANT::Profile::Profile(uint8_t channel_number, ANT::Ant * protocol)
: _channel_number(channel_number)
, _ant(protocol)
, _sport_mode(0)
{}

ANT::Profile::~Profile()
{}

uint8_t ANT::Profile::channelNumber()
{
	return _channel_number;
}
