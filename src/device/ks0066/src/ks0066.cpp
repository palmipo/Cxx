#include "ks0066.h"
#include "ks0066_io.h"

KS0066::KS0066(KS0066_io * io)
: _io(io)
{
	_io->set_enable(1);
}


KS0066::~KS0066()
{
}


void KS0066::clear_display()
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(1);
}

void KS0066::return_home()
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(2);
}


void KS0066::set_entry_mode(uint8_t i_d, uint8_t sh)
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(0x04 | (i_d << 1) | sh );
}


void KS0066::set_display_control(uint8_t d, uint8_t c, uint8_t b)
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(0x08 | (d << 2) | (c << 1) | b );
}


void KS0066::set_cursor_display_shift(uint8_t s_c, uint8_t r_l)
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(0x10 | (s_c << 3) | (r_l << 2));
}


void KS0066::set_function(uint8_t dl, uint8_t n, uint8_t f)
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(0x20 | (dl << 4) | (n << 3) | (f << 2));
}


void KS0066::set_cgram_address(uint8_t ac)
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(0x40 | (ac & 0x3F));
}


void KS0066::set_ddram_address(uint8_t ac)
{
	while(!read_busy_flag_address());
	_io->set_register_select(0);
	_io->set_read_write_(0);
	_io->set_data(0x80 | (ac & 0x7F));
}


uint8_t KS0066::read_busy_flag_address(uint8_t * address)
{
	_io->set_register_select(0);
	_io->set_read_write_(1);
	uint8_t data = _io->get_data();
	if (address) { *address = data & 0x7F; }
	return (data & 0x80) ? 1 : 0;
}


void KS0066::write_data_to_ram(uint8_t data)
{
	while(!read_busy_flag_address());
	_io->set_register_select(1);
	_io->set_read_write_(0);
	_io->set_data(data);
}


uint8_t KS0066::read_data_from_ram()
{
	while(!read_busy_flag_address());
	_io->set_register_select(1);
	_io->set_read_write_(1);
	uint8_t data = _io->get_data();
	return data;
}


