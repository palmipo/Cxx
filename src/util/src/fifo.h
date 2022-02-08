#ifndef FIFO_H
#define FIFO_H

#include <cstdint>

class Fifo
{
	public:
		Fifo(int32_t);
		virtual ~Fifo();
	
		int32_t read(uint8_t *, int32_t);
		int32_t readOver(int32_t, uint8_t *, int32_t);
		int32_t write(uint8_t *, int32_t);
		int32_t getUnread(uint8_t *, int32_t);
	
	protected:
		int32_t _max_buffer;
		uint8_t *_buffer;
		int32_t _i_read;
		int32_t _i_write;
};

#endif
