#include "uart.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

// uart0 / uart1
// parity : UART_PARITY_NONE, UART_PARITY_EVEN, UART_PARITY_ODD
Uart::Uart(uart_inst_t * uart, uint32_t tx_pin, uint32_t baud_rate, uint32_t rx_pin, uint32_t data_bits, uint32_t stop_bits, uart_parity_t parity)
: _uart(uart)
, _chars_rxed(0)
{
	uart_init(_uart, baud_rate);

	gpio_set_function(tx_pin, GPIO_FUNC_UART);
	gpio_set_function(rx_pn, GPIO_FUNC_UART);

	uart_set_hw_flow(_uart, false, false);
	uart_set_format(_uart, data_bits, stop_bits, parity);
	uart_set_fifo_enabled(_uart, false);
	irq_set_exclusive_handler(_uart, on_uart_rx);
	irq_set_enabled(_uart, true);
	uart_set_irq_enables(_uart, true, false);
}

// RX interrupt handler
void Uart::on_uart_rx() {
    while (uart_is_readable(_uart)) {
        uint8_t ch = uart_getc(_uart);
        // Can we send it back?
        if (uart_is_writable(_uart)) {
            // Change it slightly first!
            ch++;
            uart_putc(_uart, ch);
        }
        _chars_rxed++;
    }
}

int32_t Uart::write(uint8_t * src, int32_t len)
{
	uart_write_blocking(_uart, src, len);
	
	return len;
}

int32_t Uart::read(uint8_t * dst, int32_t len)
{
	uart_read_blocking(_uart, dst, len);
	
	return len;
}
