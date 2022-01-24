#include "fifo.h"

Fifo::Fifo(int32_t taille)
: _max_buffer(taille)
, _buffer(new uint8_t[_max_buffer])
, _i_read(0)
, _i_write(0)
{}

Fifo::~Fifo()
{
	delete[] _buffer;
}
	
int32_t Fifo::read(uint8_t *data, int32_t length)
{
	for (int32_t i=0; i<length; i+=1)
	{
		data[i] = _buffer[_i_read];
		if (_i_read < _max_buffer)
		{
			_i_read += 1;
		}
		else
		{
			_i_read = 0;
		}
	}
	return length;
}

int32_t Fifo::write(uint8_t *data, int32_t length)
{
	for (int32_t i=0; i<length; i+=1)
	{
		_buffer[_i_write] = data[i];
		if (_i_write < _max_buffer)
		{
			_i_write += 1;
		}
		else
		{
			_i_write = 0;
		}
	}
	return length;
}
