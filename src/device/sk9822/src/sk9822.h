#ifndef SK9822_H
#define SK9822_H

#include <cstdint>
#include <string>

class SK9822_io;
class SK9822
{
	public:
		SK9822(SK9822_io *);
		virtual ~SK9822();
	
		void write(uint32_t*, uint32_t);
	
	protected:
		void start_frame();
		void stop_frame();
		void data_frame(uint8_t, uint8_t, uint8_t, uint8_t);
	
	protected:
		SK9822_io * _io;
};

#endif
