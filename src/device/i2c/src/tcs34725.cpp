#include "tcs34725.h"
#include "i2c.h"
#include "log.h"

#define TCS34725_ENABLE (0x00)      /**< Interrupt Enable register */
#define TCS34725_ATIME (0x01) /**< Integration time */
#define TCS34725_WTIME (0x03) /**< Wait time (if TCS34725_ENABLE_WEN is asserted) */
#define TCS34725_AILTL (0x04) /**< Clear channel lower interrupt threshold (lower byte) */
#define TCS34725_AILTH (0x05) /**< Clear channel lower interrupt threshold (higher byte) */
#define TCS34725_AIHTL (0x06) /**< Clear channel upper interrupt threshold (lower byte) */
#define TCS34725_AIHTH (0x07) /**< Clear channel upper interrupt threshold (higher byte) */
#define TCS34725_PERS (0x0C) /**< Persistence register - basic SW filtering mechanism for interrupts */
//~ #define TCS34725_PERS_NONE (0b0000) /**< Every RGBC cycle generates an interrupt */
//~ #define TCS34725_PERS_1_CYCLE (0b0001) /**< 1 clean channel value outside threshold range generates an interrupt */
#define TCS34725_CONFIG (0x0D) /**< Configuration **/
#define TCS34725_CONTROL (0x0F) /**< Set the gain level for the sensor */
#define TCS34725_ID (0x12) /**< 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727 */
#define TCS34725_STATUS (0x13)      /**< Device status **/
#define TCS34725_CDATAL (0x14) /**< Clear channel data low byte */
#define TCS34725_CDATAH (0x15) /**< Clear channel data high byte */
#define TCS34725_RDATAL (0x16) /**< Red channel data low byte */
#define TCS34725_RDATAH (0x17) /**< Red channel data high byte */
#define TCS34725_GDATAL (0x18) /**< Green channel data low byte */
#define TCS34725_GDATAH (0x19) /**< Green channel data high byte */
#define TCS34725_BDATAL (0x1A) /**< Blue channel data low byte */
#define TCS34725_BDATAH (0x1B) /**< Blue channel data high byte */

TCS34725::TCS34725(I2C * i2c_ctrl)
: DeviceI2C(0x29, i2c_ctrl)
{}

void TCS34725::on(uint8_t AIEN, double ATIME, double WTIME, uint8_t WLONG, uint8_t AGAIN, uint8_t APERS)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "on");

	uint8_t buffer[2];
	buffer[0] = cmd_register(1, 0, TCS34725_ENABLE);
	buffer[1] = enable_register(AIEN, 1, 1, 1);
	_twi->set (_address, buffer, 2);

	buffer[0] = cmd_register(1, 0, TCS34725_ATIME);
	buffer[1] = RGBC_timing_register(ATIME);
	_twi->set (_address, buffer, 2);

	buffer[0] = cmd_register(1, 0, TCS34725_WTIME);
	buffer[1] = wait_time_register(WTIME);
	_twi->set (_address, buffer, 2);
	Log::getLogger()->debug(__FILE__, __LINE__, "enable_register");

/*
The configuration register sets the wait long time.
*/
	buffer[0] = cmd_register(1, 0, TCS34725_CONFIG);
	buffer[1] = configuration_register(WLONG);
	_twi->set (_address, buffer, 2);
	Log::getLogger()->debug(__FILE__, __LINE__, "configuration_register");

/*
The Control register provides eight bits of miscellaneous 
control to the analog block. These bits typically control 
functions such as gain settings and/or diode selection.
*/
	buffer[0] = cmd_register(1, 0, TCS34725_CONTROL);
	buffer[1] = control_register(AGAIN);
	_twi->set (_address, buffer, 2);
	Log::getLogger()->debug(__FILE__, __LINE__, "control_register");

/*
The persistence register controls the filtering interrupt 
capabilities of the device. Configurable filtering is provided to 
allow interrupts to be generated after each integration cycle or 
if the integration has produced a result that is outside of the 
values specified by the threshold register for some specified 
amount of time.
*/
	buffer[0] = cmd_register(1, 0, TCS34725_PERS);
	buffer[1] = persistence_register(APERS);
	_twi->set (_address, buffer, 2);
}

void TCS34725::off()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "off");

	uint8_t buffer[2];

	buffer[0] = cmd_register(1, 0, TCS34725_ENABLE);
	buffer[1]  = enable_register(0, 0, 0, 0);
	_twi->set (_address, buffer, 2);
}

/*
The persistence register controls the filtering interrupt 
capabilities of the device. Configurable filtering is provided to 
allow interrupts to be generated after each integration cycle or 
if the integration has produced a result that is outside of the 
values specified by the threshold register for some specified 
amount of time.
The RGBC interrupt threshold registers provides the values to 
be used as the high and low trigger points for the comparison 
function for interrupt generation. If the value generated by the 
clear channel crosses below the lower threshold specified, or 
above the higher threshold, an interrupt is asserted on the 
interrupt pin
*/
void TCS34725::setClearInterruptThreshold(uint8_t APERS, uint16_t low_threahold, uint16_t high_threahold)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "setClearInterruptThreshold");

	uint8_t buffer[5];

	buffer[0] = cmd_register(1, 1, TCS34725_AILTL);
	buffer[1]  = low_threahold & 0x00FF;
	buffer[2]  = (low_threahold & 0xFF00) >> 8;
	buffer[3]  = high_threahold & 0x00FF;
	buffer[4]  = (high_threahold & 0xFF00) >> 8;
	_twi->set (_address, buffer, 5);
	
	buffer[0] = cmd_register(1, 0, TCS34725_PERS);
	buffer[1] = persistence_register(APERS);
	_twi->set (_address, buffer, 2);
}

void TCS34725::clearChannelInterruptClear()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "clearChannelInterruptClear");

	uint8_t buffer;
	buffer = cmd_register(1, 3, 6);
	_twi->set (_address, &buffer, 1);
}

/*
The ID Register provides the value for the part number. The ID 
register is a read-only register.
*/
uint8_t TCS34725::id()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "id");

	uint8_t cmd = cmd_register(1, 0, TCS34725_ID);
	uint8_t buffer;
	_twi->transfert (_address, &cmd, 1, &buffer, 1);
	
	return buffer;
}

/*
The Status Register provides the internal status of the device. 
This register is read only. 
*/
uint8_t TCS34725::status(uint8_t * AINT)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "status");

	uint8_t cmd = cmd_register(1, 0, TCS34725_STATUS);
	uint8_t buffer;
	_twi->transfert (_address, &cmd, 1, &buffer, 1);
	
	if (AINT) *AINT = (buffer & 0x10) ? 0x01 : 0x00;
	return (buffer & 0x01) ? 0x01 : 0x00;
}

/*
Clear, red, green, and blue data is stored as 16-bit values. To 
ensure the data is read correctly, a two-byte read I�C transaction 
should be used with a read word protocol bit set in the 
command register. With this operation, when the lower byte 
register is read, the upper eight bits are stored into a shadow 
register, which is read by a subsequent read to the upper byte. 
The upper register will read the correct value even if additional 
ADC integration cycles end between the reading of the lower 
and upper registers.
*/
void TCS34725::readChannels(uint16_t * c, uint16_t * r, uint16_t * g, uint16_t * b)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "readChannels");

	uint8_t cmd = cmd_register(1, 1, TCS34725_CDATAL);

	uint32_t buffer_len = 8;
	uint8_t buffer[buffer_len];

	_twi->transfert (_address, &cmd, 1, buffer, buffer_len);
	
	*c = buffer[0] | (buffer[1] << 8);
	*r = buffer[2] | (buffer[3] << 8);
	*g = buffer[4] | (buffer[5] << 8);
	*b = buffer[6] | (buffer[7] << 8);
}

uint16_t TCS34725::clearChannel()
{
	uint32_t cmd_len = 1;
	uint8_t cmd[cmd_len];
	cmd[0] = cmd_register(0, 1, TCS34725_CDATAL);

	uint32_t buffer_len = 2;
	uint8_t buffer[buffer_len];

	_twi->transfert (_address, cmd, cmd_len, buffer, buffer_len);
	
	return buffer[0] | (buffer[1] << 8);
}

uint16_t TCS34725::redChannel()
{
	uint32_t cmd_len = 1;
	uint8_t cmd[cmd_len];
	cmd[0] = cmd_register(0, 1, TCS34725_RDATAL);

	uint32_t buffer_len = 2;
	uint8_t buffer[buffer_len];

	_twi->transfert (_address, cmd, cmd_len, buffer, buffer_len);
	
	return buffer[0] | (buffer[1] << 8);
}

uint16_t TCS34725::greenChannel()
{
	uint32_t cmd_len = 1;
	uint8_t cmd[cmd_len];
	cmd[0] = cmd_register(0, 1, TCS34725_GDATAL);

	uint32_t buffer_len = 2;
	uint8_t buffer[buffer_len];

	_twi->transfert (_address, cmd, cmd_len, buffer, buffer_len);
	
	return buffer[0] | (buffer[1] << 8);
}

uint16_t TCS34725::blueChannel()
{
	uint32_t cmd_len = 1;
	uint8_t cmd[cmd_len];
	cmd[0] = cmd_register(0, 1, TCS34725_BDATAL);

	uint32_t buffer_len = 2;
	uint8_t buffer[buffer_len];

	_twi->transfert (_address, cmd, cmd_len, buffer, buffer_len);
	
	return buffer[0] | (buffer[1] << 8);
}

/*
 * type :
 * 00 Repeated byte protocol transaction
 * 01 Auto-increment protocol transaction
 * 10 Reserved — Do not use
 * 11 Special function
 */
uint8_t TCS34725::cmd_register(uint8_t cmd_reg, uint8_t type, uint8_t addr)
{
	return ((cmd_reg?0x01:0x00) << 7) | ((type & 0x03) << 5) | (addr & 0x1F);
}

/*
 * Reserved 7:5 Reserved. Write as 0.
 * AIEN 4 RGBC interrupt enable. When asserted, permits RGBC interrupts to be generated.
 * WEN 3 Wait enable. This bit activates the wait feature. Writing a 1 activates the wait timer. Writing a 0 disables the wait timer.
 * Reserved 2 Reserved. Write as 0.
 * AEN 1 RGBC enable. This bit actives the two-channel ADC. Writing a 1 activates the RGBC. Writing a 0 disables the RGBC.
 * PON 0 Power ON. This bit activates the internal oscillator to permit the timers and ADC channels to operate. Writing a 1 activates the oscillator. Writing a 0 disables the oscillator.
 */
uint8_t TCS34725::enable_register(uint8_t AIEN, uint8_t WEN, uint8_t AEN, uint8_t PON)
{
	return ((AIEN ? 0x01 : 0) << 4) | ((WEN ? 0x01 : 0) << 3) | ((AEN ? 0x01 : 0) << 1) | (PON ? 0x01 : 0);
}

/*
The RGBC timing register controls the internal integration time 
of the RGBC clear and IR channel ADCs in 2.4-ms increments. 
Max RGBC Count = (256 - ATIME) * 1024 up to a maximum of 
65535
*/
uint8_t TCS34725::RGBC_timing_register(double ATIME)
{
	return (256 - (int8_t)(ATIME/2.4));
}

/*
Wait time is set 2.4 ms increments unless the WLONG bit is 
asserted, in which case the wait times are 12*longer. WTIME is 
programmed as a 2's complement number
*/
uint8_t TCS34725::wait_time_register(double WTIME)
{
	return (256 - (int8_t)(WTIME/2.4));
}

/*
The persistence register controls the filtering interrupt 
capabilities of the device. Configurable filtering is provided to 
allow interrupts to be generated after each integration cycle or 
if the integration has produced a result that is outside of the 
values specified by the threshold register for some specified 
amount of time
*/
uint8_t TCS34725::persistence_register(uint8_t APERS)
{
	return (APERS & 0x0F);
}

/*
The configuration register sets the wait long time 
*/
uint8_t TCS34725::configuration_register(uint8_t WLONG)
{
	return ((WLONG ? 0x1 : 0) << 1);
}

/*
The Control register provides eight bits of miscellaneous 
control to the analog block. These bits typically control 
functions such as gain settings and/or diode selection
*/
uint8_t TCS34725::control_register(uint8_t AGAIN)
{
	return (AGAIN & 0x03);
}
