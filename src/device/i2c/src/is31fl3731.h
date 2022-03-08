#ifndef IS31FL3731_H
#define IS31FL3731_H

#include "devicei2c.h"
#include <vector>

class CtrlI2C;
class IS31FL3731 : public DeviceI2C
{
	public:
		IS31FL3731(uint8_t, CtrlI2C *);
		virtual ~IS31FL3731();
		
		virtual void shutdown(uint8_t on);

		void led(uint8_t page, uint8_t index, uint8_t on, uint8_t blink, uint8_t pwm);
		void Picture_Mode(uint8_t picture_display_selection, uint8_t Blink_Period_Time); // Blink_Period_Time = 0:fixe ; 1:rapide ; 7:lent
		void Picture_Display(uint8_t picture_display_selection, uint8_t Fade_Out_Time, uint8_t Fade_In_Time, uint8_t Breath_Enable, uint8_t Extinguish_Time);
		void Auto_Frame_Play_Mode(uint8_t Number_Loops_Playing_Selection, uint8_t Number_Frames_Playing_Selection, uint8_t Frame_Delay_Time);
		void Audio_Frame_Play_Mode();

	protected:
		uint8_t Command_Register(uint8_t Frame_Register);
		uint8_t Configuration_Register(uint8_t display_mode, uint8_t frame_start);
		uint8_t Picture_Display_Register(uint8_t picture_display_selection);
		uint8_t Auto_Play_Control_Register_1(uint8_t Number_Loops_Playing_Selection, uint8_t Number_Frames_Playing_Selection);
		uint8_t Auto_Play_Control_Register_2(uint8_t Frame_Delay_Time);
		uint8_t Display_Option_Register(uint8_t Intensity_Control, uint8_t Blink_Enable, uint8_t Blink_Period_Time);
		void    Frame_State_Register(uint8_t reg, uint8_t * INT, uint8_t * CFD);
		uint8_t Breath_Control_Register_1(uint8_t Fade_Out_Time, uint8_t Fade_In_Time);
		uint8_t Breath_Control_Register_2(uint8_t Breath_Enable, uint8_t Extinguish_Time);
		uint8_t Shutdown_Register(uint8_t Shutdown_Control);
		uint8_t AGC_Control_Register(uint8_t AGC_Mode, uint8_t AGC_Enable, uint8_t Audio_Gain_Selection);
		uint8_t Audio_ADC_Rate_Register(uint8_t Audio_ADC_Rate);
		
		// 8*9*2 leds maxi
		std::vector < uint8_t > _on;
		std::vector < uint8_t > _blink;
		std::vector < uint8_t > _pwm;
		
};

#endif /* IS31FL3731_H */
