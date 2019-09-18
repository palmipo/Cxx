#ifndef TCS34725_H
#define TCS34725_H

#include "devicei2c.h"

/* i2c_addr = 0x29 */

class I2C;
class TCS34725 : public DeviceI2C
{
	public:
		TCS34725(I2C * i2c_ctrl);
		virtual void on(uint8_t AIEN, double ATIME, double WTIME, uint8_t WLONG, uint8_t AGAIN);
		virtual void off();
		virtual void setClearInterruptThreshold(uint8_t APERS, uint16_t low_threahold, uint16_t high_threahold);
		virtual void clearChannelInterruptClear();
		virtual uint8_t id();
		virtual uint8_t status(uint8_t * AINT=0);
		virtual void readChannels(uint16_t * c, uint16_t * r, uint16_t * g, uint16_t * b);
		virtual uint16_t clearChannel();
		virtual uint16_t redChannel();
		virtual uint16_t greenChannel();
		virtual uint16_t blueChannel();

	protected:
		/*
		 * type :
		 * 00 Repeated byte protocol transaction
		 * 01 Auto-increment protocol transaction
		 * 10 Reserved — Do not use
		 * 11 Special function
		 */
		uint8_t cmd_register(uint8_t cmd_reg, uint8_t type, uint8_t addr);

		/*
		 * Reserved 7:5 Reserved. Write as 0.
		 * AIEN 4 RGBC interrupt enable. When asserted, permits RGBC interrupts to be generated.
		 * WEN 3 Wait enable. This bit activates the wait feature. Writing a 1 activates the wait timer. Writing a 0 disables the wait timer.
		 * Reserved 2 Reserved. Write as 0.
		 * AEN 1 RGBC enable. This bit actives the two-channel ADC. Writing a 1 activates the RGBC. Writing a 0 disables the RGBC.
		 * PON 0 Power ON. This bit activates the internal oscillator to permit the timers and ADC channels to operate. Writing a 1 activates the oscillator. Writing a 0 disables the oscillator.
		 */
		uint8_t enable_register(uint8_t AIEN, uint8_t WEN, uint8_t AEN, uint8_t PON);

		/*
		The RGBC timing register controls the internal integration time 
		of the RGBC clear and IR channel ADCs in 2.4-ms increments. 
		Max RGBC Count = (256 − ATIME) × 1024 up to a maximum of 
		65535
		*/
		uint8_t RGBC_timing_register(double ATIME);

		/*
		Wait time is set 2.4 ms increments unless the WLONG bit is 
		asserted, in which case the wait times are 12× longer. WTIME is 
		programmed as a 2’s complement number
		*/
		uint8_t wait_time_register(double WTIME);

		/*
		The RGBC interrupt threshold registers provides the values to 
		be used as the high and low trigger points for the comparison 
		function for interrupt generation. If the value generated by the 
		clear channel crosses below the lower threshold specified, or 
		above the higher threshold, an interrupt is asserted on the 
		interrupt pin
		*/
		uint8_t RGBC_interrupt_threshold_registers(uint16_t low, uint16_t high);

		/*
		The persistence register controls the filtering interrupt 
		capabilities of the device. Configurable filtering is provided to 
		allow interrupts to be generated after each integration cycle or 
		if the integration has produced a result that is outside of the 
		values specified by the threshold register for some specified 
		amount of time
		*/
		uint8_t persistence_register(uint8_t APERS);

		/*
		The configuration register sets the wait long time 
		*/
		uint8_t configuration_register(uint8_t WLONG);

		/*
		The Control register provides eight bits of miscellaneous 
		control to the analog block. These bits typically control 
		functions such as gain settings and/or diode selection
		*/
		uint8_t control_register(uint8_t AGAIN);
};

#endif /* TCS34725_H */
