#include "antprofile.h"
#include "ant.h"
#include <iostream>

/*
0 Data Page Number // 1 Byte // 70 (0x46) Data Page Request N/A
1 Reserved // 1 Byte // Value = 0xFF N/A
2 Reserved // 1 Byte // Value = 0xFF N/A
3 Descriptor Byte 1 // 1 Byte // Allows subpages to be requested within the requested data page.
	Valid Values: 0 – 254
	Invalid: 255 (0xFF) N/A
4 Descriptor Byte 2 // 1 Byte // Allows subpages to be requested within the requested data page.
	Valid Values: 0 – 254
	Invalid: 255 (0xFF) N/A
5 Requested Transmission Response // 1 Byte // Describes transmission characteristics of the data requested.
	Bit 0-6: Number of times to transmit requested page.
	Bit 7: Setting the MSB means the device replies using acknowledged messages if possible.
	Special Values: 0x80 - Transmit until a successful acknowledge is received.
	0x00 – Invalid N/A
6 Requested Page Number // 1 Byte // Page number to transmit. N/A
7 Command Type // 1 Byte // Value = 1 (0x01) for Request Data Page Value = 2 (0x02) for Request ANT-FS session N/A
*/
void ANT::Profile::requestDataPage(uint8_t page_number)
{
	uint8_t len = 8;
	uint8_t msg[] = { 0x46, 0xFF, 0xFF, 0xFF, 0xFF, 1, page_number, 1 };
	_ant->acknowledgedData(_channel_number, msg, len);
}

/*
0 Data Page Number 1 Byte 76 (0x4C) Mode Settings Page N/A
1 Reserved 1 Byte Reserved: Set to 0xFF N/A
2 Reserved 1 Byte Reserved: Set to 0xFF N/A
3 Reserved 1 Byte Reserved: Set to 0xFF N/A
4 Reserved 1 Byte Reserved: Set to 0xFF N/A
5 Reserved 1 Byte Reserved: Set to 0xFF N/A
6 Reserved 1 Byte Reserved: Set to 0xFF N/A
7 Sport Mode 1 Byte 0x01: Running 0x02: Cycling 0x05: Swimming Refer to FIT SDK for Sport enum N/A
*/
void ANT::Profile::modeSettingsPage(uint8_t sport_mode)
{
	uint8_t len = 8;
	uint8_t msg[] = { 0x4C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, sport_mode};
	_ant->broadcastData(_channel_number, msg, len);
}
/*
0 Data Page Number 1 Byte 78 (0x4E) Multi-component System Manufacturers Information N/A
1 Reserved 1 Byte Value = 0xFF N/A
2 Component Identifier 1 Byte Identifies the component in the system to which this Manufacturer’s Information pertains and specifies how many separate components are available in the system. Bits 0 – 3: Number of Components Bits 4 – 7: Component Identifier (Refer to the relevant ANT+ device profile) Set to 0xFF if not used. N/A
3 HW Revision 1 Byte To be set by the manufacturer. N/A
4 Manufacturer ID LSB 2 Bytes Refer to the FIT SDK for a current list of manufacturer IDs N/A
5 Manufacturer ID MSB
6 Model Number LSB 2 Bytes To be set by the manufacturer. N/A
7 Model Number MSB
*/
/*
0 Data Page Number 1 Byte 79 (0x4F) Multi-component System Product Information N/A
1 Component Identifier 1 Byte Identifies the component in the system to which this Manufacturer’s Information pertains and specifies how many separate components are available in the system. Bits 0 – 3: Number of Components Bits 4 – 7: Component Identifier (Refer to the relevant ANT+ device profile) Set to 0xFF if not used. N/A
2 SW Revision (Supplemental) 1 Byte Supplemental SW Revision (Invalid = 0xFF) N/A
3 SW Revision (Main) 1 Byte Main SW Revision defined by manufacturer OR: SW version defined by manufacturer if byte 2 is set to 0xFF. N/A
4 Serial Number (Bits 0 – 7) 4 Bytes The lowest 32 bits of the serial number. Value 0xFFFFFFFF to be used for devices without serial numbers N/A
5 Serial Number (Bits 8 – 15)
6 Serial Number (Bits 16 – 23)
7 Serial Number (Bits 24 – 31)
*/
/*
0 Data Page Number 1 Byte 0x50 Common Page 80 N/A
1 Reserved 1 Byte Value = 0xFF N/A
2 Reserved 1 Byte Value = 0xFF
3 HW Revision 1 Byte To be set by the manufacturer. N/A
4 Manufacturer ID LSB 2 Bytes Contact the ANT+ Alliance for a current list of manufacturing IDs, or to be assigned a manufacturing ID. N/A
5 Manufacturer ID MSB
6 Model Number LSB 2 Bytes To be set by the manufacturer. N/A
7 Model Number MSB
*/
void ANT::Profile::sendManufacturerIdentification()
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x50;
	msg[1] = 0xFF;
	msg[2] = 0xFF;
	msg[3] = _hw_revision;
	msg[4] = _manufacturer_id & 0x00FF;
	msg[5] = (_manufacturer_id & 0xFF00) >> 8;
	msg[6] = _model_number & 0x00FF;
	msg[7] = (_model_number & 0xFF00) >> 8;
	_ant->broadcastData(_channel_number, msg, len);
}

/*
0 Data Page Number // 1 Byte // 0x51 Common Page 81 N/A
1 Reserved // 1 Byte // Value = 0xFF N/A
2 Reserved // 1 Byte // Value = 0xFF N/A
3 SW Revision // 1 Byte // To be set by the manufacturer. N/A
4 Serial Number (Bits 0 – 7) 4 Bytes The lowest 32 bits of the serial number. Value 0xFFFFFFFF to be used for devices without serial numbers. N/A
5 Serial Number (Bits 8 – 15)
6 Serial Number (Bits 16 – 23)
7 Serial Number (Bits 24 – 31)
*/
void ANT::Profile::sendProductInformation()
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x51;
	msg[1] = 0xFF;
	msg[2] = 0xFF;
	msg[3] = _sw_revision;
	msg[4] = _serial_number & 0x000000FF;
	msg[5] = (_serial_number & 0x0000FF00) >> 8;
	msg[6] = (_serial_number & 0x00FF0000) >> 16;
	msg[7] = (_serial_number & 0xFF000000) >> 24;
	_ant->broadcastData(_channel_number, msg, len);
}
/*
0 Data Page Number // 1 Byte 82 (0x52) // Battery Status
1 Reserved // 1 Byte // Value = 0xFF
2 Battery Identifier // 1 Byte // Identifies the battery in system to which this battery status pertains and specifies how many batteries are available in the system. Bits 0 – 3: Number of Batteries Bits 4 – 7: Identifier Set to 0xFF if not used. N/A N/A
3 Cumulative Operating Time (bits 0 a 7) // 3 Bytes // This will give the cumulative operating time of the device and should be reset on insertion of a new battery. Range = 0 – 16777215 ticks 2 seconds 16 seconds 1.1 years 8.5 years
4 Cumulative Operating Time (bits 8 a 15)
5 Cumulative Operating Time (bits 16 a 23)
6 Fractional Battery Voltage // 1 Byte // Value = 0 a 255 (0x00 a 0xFF) 1/256 (V) N/A
7 Descriptive Bit Field // 1 Byte // Battery Status, Cumulative Operating Time Resolution, and Coarse Battery Voltage See Table 6-14 for more details. Binary N/A
0 – 3 0 – 14 Volts 0xF (15): Invalid Coarse Battery Voltage Use bit mask of 0x0F
4 – 6 0 Reserved for future use 1 Battery Status = New 2 Battery Status = Good 3 Battery Status = Ok 4 Battery Status = Low 5 Battery Status = Critical 6 Reserved for future use 7 Invalid
7 0 – 16 second resolution 1 – 2 second resolution The resolution used for the cumulative operating time
*/
void ANT::Profile::sendBatteryStatus()
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x52;
	msg[1] = 0xFF;
	msg[2] = _battery_identifier;
	msg[3] = _cumulative_operatging_time & 0x000000FF;
	msg[4] = (_cumulative_operatging_time & 0x0000FF00) >> 8;
	msg[5] = (_cumulative_operatging_time & 0x00FF0000) >> 16;
	msg[6] = _fractional_battery_voltage;
	msg[7] = (_coarse_battery_voltage_use & 0xF) | ((_battery_status & 0x7) << 4) | ((_resolution & 0x01) << 7);
	_ant->broadcastData(_channel_number, msg, len);
}

/*
0 Page Number // 1 Byte 83 (0x53) – Time and Date
1 Reserved // 1 Byte 0xFF
2 Seconds // 1 Byte The number of seconds. Valid data range = 0 – 59
3 Minutes // 1 Byte The number of minutes. Valid data range = 0 - 59
4 Hours // 1 Byte The current hour of the day in a 24 hour clock. Valid data range = 0 - 23
5 Day of Week
 3 Bits (bits 7-5 of Byte 6) Sunday = 0, Monday = 1, …, Saturday = 6 Invalid = 7
 5 Bits (bits 4-0 of Byte 6) The day of the month. Valid data range = 1 - 31
6 Month // 1 Byte The month of the year. Valid data range = 1 - 12
7 Year // 1 Byte The year since the year 2000. Valid data range = 0 - 255
*/
void ANT::Profile::sendTimeDate(uint8_t heure, uint8_t minute, uint8_t seconde, uint8_t jour, uint8_t mois, uint8_t annee)
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x53;
	msg[1] = 0xFF;
	msg[2] = seconde;
	msg[3] = minute;
	msg[4] = heure;
	msg[5] = jour;
	msg[6] = mois;
	msg[7] = annee;
	_ant->broadcastData(_channel_number, msg, len);
}

/*
0 Data Page Number 1 Byte 0x55 – Common Page 85 N/A
1 Reserved 1 Byte Value = 0xFF N/A
2 Reserved 1 Byte Value = 0xFF N/A
3 Reserved 1 Byte Value = 0xFF N/A
4 % Used 1 Byte 0 – 100 % in 0.5% increments 0.5 %
5 Total Size LSB 1 Byte Total Memory Size in 0.1 increments Max 6553.5 N/A
6 Total Size MSB
7 Total Size Unit 1 Byte Bit 7: 0 – bit 1 – byte Bit 0 - 6: 000000 – base unit 000001 – kilo 000010 – Mega 000011 – Tera 000100 to 000101 - reserved N/A
*/
void ANT::Profile::sendMemory()
{
	uint8_t len = 8;
	uint8_t msg[8];
	msg[0] = 0x55;
	msg[1] = 0xFF;
	msg[2] = 0xFF;
	msg[3] = 0xFF;
	msg[4] = 0;
	msg[5] = 0;
	msg[6] = 0;
	msg[7] = 0;
	_ant->broadcastData(_channel_number, msg, len);
}

/*
0 Data Page Number 1 Byte 0x56 – Common Page 86 N/A
1 Peripheral Device Index 1 Byte If multiple peripheral devices are in the system, this field provides an index to which device is being referenced. N/A
2 Total Number of connected devices 1 Byte Provides the total number of peripheral devices in a system.
3 Channel State // 1 Byte // Bit 7: Paired/Unpaired 1 – paired 0 – not paired Bits 3:6: Connection State 0 – closed channel 1 – searching 2 – synchronised 3:F – reserved Bits 0:2: Network Key 0 – public 1 – private 2 – ANT+ Managed 3 – ANT-FS key 4:7 – reserved N/A
4 Peripheral Device ID: Device Number LSB 2 Bytes Provides the Device Number of the peripheral device indexed in byte 1 N/A
5 Peripheral Device ID: Device Number MSB
6 Peripheral Device ID: Transmission Type 1 Byte Provides the Transmission Type of the peripheral device indexed in byte 1 N/A
7 Peripheral Device ID: Device Type 1 Byte Provides the Device Type of the peripheral device indexed in byte 1 N/A
*/
/*
0 Data Page Number // 1 Byte // Data Page Number = 87 (0x57) N/A
1 Reserved // 1 Byte // Reserved: Set to 0xFF N/A
2 System Component Index // 4 Bits 
	(0:3) System Component Identifier (defined by manufacturer)
	 0xF: Invalid, System Error N/A Reserved 2 Bits
	(4:5) Reserved. Set to 0b00. N/A Error Level 2 Bits
	(6:7) 0: Reserved 1-2: Refer to Table 6-21. 3: Reserved N/A
3 Profile Specific Error Codes // 1 Byte
 The purpose of the profile specific error codes is to define error codes required for interoperability across different manufacturers.
 Refer to the relevant ANT+ device profile for definition.
 0xFF: Invalid N/A
4-7 Manufacturer Specific Error Codes // 4 Bytes // Defined by the manufacturer. 0xFFFFFFFF: Invalid N/A
*/
