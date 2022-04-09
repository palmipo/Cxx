#include "picouart.h"
#include "hardware/PicoUart.h"
#include "hardware/irq.h"

// parity : UART_PARITY_NONE, UART_PARITY_EVEN, UART_PARITY_ODD
PicoUart::PicoUart(uart_inst_t * uart, uint32_t tx_pin, uint32_t rx_pin)
: _uart(uart)
, _chars_rxed(0)
{
	PicoUart_init(_PicoUart, 9600);

	gpio_set_function(tx_pin, GPIO_FUNC_UART);
	gpio_set_function(rx_pn, GPIO_FUNC_UART);
}

PicoUart::~PicoUart()
{}

void PicoUart::setHardwareFlow(uint8_t hw_flow)
{
	uint8_t flow = hw_flow ? true : false;
	uart_set_hw_flow(_uart, flow, flow);
}

void PicoUart::setFifo(uint8_t fifo)
{
	uart_set_fifo_enabled(_uart, fifo ? true : false);
}

void PicoUart::setInterruption()
{
	irq_set_exclusive_handler(_uart, on_PicoUart_rx);
	irq_set_enabled(_uart, true);
	uart_set_irq_enables(_uart, true, false);
}

void PicoUart::setConfiguration(uint32_t baud_rate, uint32_t data_bits, PicoUart_parity_t parity, uint32_t stop_bits)
{
	uart_set_format(_uart, data_bits, stop_bits, parity);
}

// RX interrupt handler
void PicoUart::on_PicoUart_rx()
{
    while (uart_is_readable(_uart))
    {
        uint8_t ch = uart_getc(_uart);
        // Can we send it back?
        if (uart_is_writable(_uart))
	{
            // Change it slightly first!
            ch++;
            uart_putc(_uart, ch);
        }
        _chars_rxed++;
    }
}

int32_t PicoUart::write(uint8_t * src, int32_t len)
{
	uart_write_blocking(_uart, src, len);
	
	return len;
}

int32_t PicoUart::read(uint8_t * dst, int32_t len)
{
	uart_read_blocking(_uart, dst, len);
	
	return len;
}
