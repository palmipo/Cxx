#ifndef KS0066_H
#define KS0066_H

class KS0066_io;
class KS0066
{
	public:
		KS0066(KS0066_io*);
		virtual ~KS0066();
	
		void clear_display();
		void return_home();
		void set_entry_mode(uint8_t, uint8_t);
		void set_display_control(uint8_t, uint8_t, uint8_t);
		void set_cursor_display_shift(uint8_t, uint8_t);
		void set_function(uint8_t, uint8_t, uint8_t);
		void set_cgram_address(uint8_t);
		void set_ddram_address(uint8_t);
		uint8_t read_busy_flag_address(uint8_t*=0);
		void write_data_to_ram(uint8_t);
		uint8_t read_data_from_ram();
	
	protected:
		KS0066_io * _io;
};

#endif
