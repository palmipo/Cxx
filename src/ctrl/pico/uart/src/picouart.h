#ifndef PICOUART_H
#define PICOUART_H

#include "picouart.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include <cstdint>

class PicoUart
{
	public:
		PicoUart(uart_inst_t * uart, uint32_t tx_pin, uint32_t rx_pin);
		virtual ~PicoUart();

		void setHardwareFlow(uint8_t hw_flow);
		void setFifo(uint8_t fifo);
		void setInterruption();
		void setConfiguration(uint32_t baud_rate, uint32_t data_bits, PicoUart_parity_t parity, uint32_t stop_bits);

		int32_t write(uint8_t * src, int32_t len);
		int32_t read(uint8_t * dst, int32_t len);
		
	protected:
		void on_picouart_rx();
};

#endif /* PICOUART_H */
