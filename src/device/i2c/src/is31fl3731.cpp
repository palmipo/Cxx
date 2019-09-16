#include "is31fl3731.h"
#include "i2c.h"
#include "log.h"
#include <sstream>
#include <iomanip>
#include <thread>

#define IS31FL3731_LED_CONTROL_REGISTER_0			0x00

#define IS31FL3731_BLINK_CONTROL_REGISTER_0			0x12

#define IS31FL3731_PWM_CONTROL_REGISTER_0			0x24

#define IS31FL3731_COMMAND_REGISTER					0xFD

#define IS31FL3731_CONFIGURATION_REGISTER			0x00
#define IS31FL3731_PICTURE_DISPLAY_REGISTER			0x01
#define IS31FL3731_AUTO_PLAY_CONTROL_REGISTER_1		0x02
#define IS31FL3731_AUTO_PLAY_CONTROL_REGISTER_2		0x03
#define IS31FL3731_DISPLAY_OPTION_REGISTER			0x05
#define IS31FL3731_AUDIO_SYNCHRONIZATION_REGISTER	0x06
#define IS31FL3731_FRAME_STATE_REGISTER				0x07
#define IS31FL3731_BREATH_CONTROL_REGISTER_1		0x08
#define IS31FL3731_BREATH_CONTROL_REGISTER_2		0x09
#define IS31FL3731_SHUTDOWN_REGISTER				0x0A
#define IS31FL3731_AGC_CONTROL_REGISTER				0x0B
#define IS31FL3731_AUDIO_ADC_RATE_REGISTER			0x0C

/*
 *
 */
IS31FL3731::IS31FL3731(uint8_t addr, I2C * i2c_ctrl)
: DeviceI2C(0x74 | (addr & 0x7), i2c_ctrl)
{
	_on.resize(0x12);
	_blink.resize(0x12);
	_pwm.resize(144);
	
	shutdown(1);

	uint8_t buffer[2];

	for (int32_t page=0; page<8; ++page)
	{
		buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
		buffer[1] = Command_Register(page);
		_twi->set(_address, buffer, 2);

		for (int32_t i=0; i<18; ++i)
		{
			//~ _on[i] = 0xFF;
			buffer[0] = IS31FL3731_LED_CONTROL_REGISTER_0 + i;
			buffer[1] = _on[i];
			_twi->set(_address, buffer, 2);

			//~ _blink[i] = 0xFF;
			buffer[0] = IS31FL3731_BLINK_CONTROL_REGISTER_0 + i;
			buffer[1] = _blink[i];
			_twi->set(_address, buffer, 2);
		}

		for (int32_t i=0; i<144; ++i)
		{
			//~ _pwm[i] = 0x0F;
			buffer[0] = IS31FL3731_PWM_CONTROL_REGISTER_0 + i;
			buffer[1] = _pwm[i];
			_twi->set(_address, buffer, 2);
		}
	}

	Picture_Mode(0, 0);
}

/*
 *
 */
IS31FL3731::~IS31FL3731()
{
	shutdown(0);
}

/*
 *
 */
void IS31FL3731::shutdown(uint8_t on)
{
	uint8_t buffer[2];

	buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
	buffer[1] = Command_Register(9);
	_twi->set(_address, buffer, 2);

	buffer[0] = IS31FL3731_SHUTDOWN_REGISTER;
	buffer[1] = Shutdown_Register(on);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "SHUTDOWN_REGISTER : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

/*
 *
 */
void IS31FL3731::led(uint8_t page, uint8_t index, uint8_t on, uint8_t blink, uint8_t pwm)
{
	uint8_t buffer[2];

	buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
	buffer[1] = Command_Register(page);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "Command_Register : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	uint8_t octet = index >> 3;
	uint8_t del = index - (octet << 3);
	_on[octet] = (_on[octet] & ~(1 << del)) | ((on?1:0) << del);
	_blink[octet] = (_blink[octet] & ~(1 << del)) | ((blink?1:0) << del);
	_pwm[octet] = pwm;
	{
		std::stringstream ss;
		ss << "on : 0x" << std::hex << (int)_on[octet] << ", 0x" << (int)_blink[octet] << ", 0x" << (int)_pwm[octet];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	buffer[0] = IS31FL3731_LED_CONTROL_REGISTER_0 + octet;
	buffer[1] = _on[octet];
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "LED_CONTROL_REGISTER : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	buffer[0] = IS31FL3731_BLINK_CONTROL_REGISTER_0 + octet;
	buffer[1] = _blink[octet];
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "BLINK_CONTROL_REGISTER : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	buffer[0] = IS31FL3731_PWM_CONTROL_REGISTER_0 + index;
	buffer[1] = _pwm[octet];
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "PWM_CONTROL_REGISTER : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
}

/*
 * PICTURE MODE
 */
void IS31FL3731::Picture_Mode(uint8_t picture_display_selection, uint8_t Blink_Period_Time)
{
	uint8_t buffer[2];

	buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
	buffer[1] = Command_Register(9);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "Command_Register : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	buffer[0] = IS31FL3731_CONFIGURATION_REGISTER;
	buffer[1] = Configuration_Register(0, picture_display_selection);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "Configuration_Register : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	
	buffer[0] = IS31FL3731_PICTURE_DISPLAY_REGISTER;
	buffer[1] = Picture_Display_Register(picture_display_selection);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "Picture_Display_Register : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	buffer[0] = IS31FL3731_DISPLAY_OPTION_REGISTER;
	buffer[1] = Display_Option_Register(0, 1, Blink_Period_Time);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "IS31FL3731_DISPLAY_OPTION_REGISTER : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
}

/*
 *
 */
void IS31FL3731::Picture_Display(uint8_t picture_display_selection, uint8_t Fade_Out_Time, uint8_t Fade_In_Time, uint8_t Breath_Enable, uint8_t Extinguish_Time)
{
	uint8_t buffer[2];

	buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
	buffer[1] = Command_Register(9);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "Command_Register : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	
	buffer[0] = IS31FL3731_PICTURE_DISPLAY_REGISTER;
	buffer[1] = Picture_Display_Register(picture_display_selection);
	_twi->set(_address, buffer, 2);
	{
		std::stringstream ss;
		ss << "Picture_Display_Register : " << std::hex << "0x" << (int)buffer[0] << ", 0x" << (int)buffer[1];
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	
	buffer[0] = IS31FL3731_BREATH_CONTROL_REGISTER_1;
	buffer[1] = Breath_Control_Register_1(Fade_Out_Time, Fade_In_Time);
	_twi->set(_address, buffer, 2);

	buffer[0] = IS31FL3731_BREATH_CONTROL_REGISTER_2;
	buffer[1] = Breath_Control_Register_2(Breath_Enable, Extinguish_Time);
	_twi->set(_address, buffer, 2);
}

/*
 * AUTO FRAME PLAY MODE
 */
void IS31FL3731::Auto_Frame_Play_Mode(uint8_t Number_Loops_Playing_Selection, uint8_t Number_Frames_Playing_Selection, uint8_t Frame_Delay_Time)
{
	uint8_t buffer[2];

	buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
	buffer[1] = Command_Register(9);
	_twi->set(_address, buffer, 2);

	buffer[0] = IS31FL3731_CONFIGURATION_REGISTER;
	buffer[1] = Configuration_Register(1, 0);
	_twi->set(_address, buffer, 2);
	
	buffer[0] = IS31FL3731_AUTO_PLAY_CONTROL_REGISTER_1;
	buffer[1] = Auto_Play_Control_Register_1(Number_Loops_Playing_Selection, Number_Frames_Playing_Selection);
	_twi->set(_address, buffer, 2);
	
	buffer[0] = IS31FL3731_AUTO_PLAY_CONTROL_REGISTER_2;
	buffer[1] = Auto_Play_Control_Register_2(Frame_Delay_Time);
	_twi->set(_address, buffer, 2);
}

/*
 * Audio Frame Play Mode
 */
void IS31FL3731::Audio_Frame_Play_Mode()
{
	uint8_t buffer[2];

	buffer[0] = IS31FL3731_COMMAND_REGISTER; // 0xFD
	buffer[1] = Command_Register(9);
	_twi->set(_address, buffer, 2);

	buffer[0] = IS31FL3731_CONFIGURATION_REGISTER;
	buffer[1] = Configuration_Register(2, 0);
	_twi->set(_address, buffer, 2);
}

/*
 * PROTECTED FUNCTIONS
 */
uint8_t IS31FL3731::Command_Register(uint8_t Frame_Register)
{
	if ((Frame_Register < 0) || (Frame_Register > 7))
	{
		return 0x0B;
	}
	else
	{
		return Frame_Register;
	}
}

uint8_t IS31FL3731::Configuration_Register(uint8_t display_mode, uint8_t frame_start)
{
	return ((display_mode & 0x3) << 3) | (frame_start & 0x7);
}

uint8_t IS31FL3731::Picture_Display_Register(uint8_t picture_display_selection)
{
	return (picture_display_selection & 0x7);
}

uint8_t IS31FL3731::Auto_Play_Control_Register_1(uint8_t Number_Loops_Playing_Selection, uint8_t Number_Frames_Playing_Selection)
{
	return ((Number_Loops_Playing_Selection & 0x7) << 4) | (Number_Frames_Playing_Selection & 0x7);
}

uint8_t IS31FL3731::Auto_Play_Control_Register_2(uint8_t Frame_Delay_Time)
{
	return (Frame_Delay_Time & 0x3F);
}

uint8_t IS31FL3731::Display_Option_Register(uint8_t Intensity_Control, uint8_t Blink_Enable, uint8_t Blink_Period_Time)
{
	return ((Intensity_Control?1:0) << 5) | ((Blink_Enable?1:0) << 3) | (Blink_Period_Time & 0x7);
}

void IS31FL3731::Frame_State_Register(uint8_t reg, uint8_t * INT, uint8_t * CFD)
{
	*INT = (reg & 0x10)? 1 : 0;
	*CFD = (reg & 0x7);
}

uint8_t IS31FL3731::Breath_Control_Register_1(uint8_t Fade_Out_Time, uint8_t Fade_In_Time)
{
	return ((Fade_Out_Time & 0x7) << 4) | (Fade_In_Time & 0x7);
}


uint8_t IS31FL3731::Breath_Control_Register_2(uint8_t Breath_Enable, uint8_t Extinguish_Time)
{
	return ((Breath_Enable? 1 : 0) << 4) | (Extinguish_Time & 0x7);
}

uint8_t IS31FL3731::Shutdown_Register(uint8_t Shutdown_Control)
{
	return (Shutdown_Control ? 1 : 0);
}

uint8_t IS31FL3731::AGC_Control_Register(uint8_t AGC_Mode, uint8_t AGC_Enable, uint8_t Audio_Gain_Selection)
{
	return ((AGC_Mode ? 1 : 0) << 4) | ((AGC_Enable ? 1 : 0) << 3) | (Audio_Gain_Selection & 0x7);
}


uint8_t IS31FL3731::Audio_ADC_Rate_Register(uint8_t Audio_ADC_Rate)
{
	return Audio_ADC_Rate;
}
