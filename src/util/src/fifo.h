#ifndef FIFO_H
#define FIFO_H

#include <cstdint>

class Fifo
{
	protected:
		int32_t _max_buffer;
		uint8_t *_buffer;
		int32_t _i_read;
		int32_t _i_write;

public:
Fifo(int32_t taille)
: _max_buffer(taille)
, _buffer(new uint8_t[_max_buffer])
, _i_read(0)
, _i_write(0)
{}

~Fifo()
{
	delete[] _buffer;
}
	
int32_t read(uint8_t *data, int32_t length)
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
	
int32_t readOver(int32_t offset, uint8_t *data, int32_t length)
{
	int32_t j = _i_read + offset;
	for (int32_t i=0; i<length; i+=1)
	{
		data[i] = _buffer[j];
		if (j < _max_buffer)
		{
			j += 1;
		}
		else
		{
			j = 0;
		}
	}
	return length;
}
	
int32_t getUnread(uint8_t * data, int32_t length)
{
	int32_t taille = _i_write - _i_read;
	if (_i_write < _i_read) taille = _max_buffer + _i_write - _i_read;
	if (taille > length) taille = length;

	int32_t j = _i_read;
	for (int32_t i=0; i<taille; i+=1)
	{
		data[i] = _buffer[j];
		if (j < _max_buffer)
		{
			j += 1;
		}
		else
		{
			j = 0;
		}
	}
	return taille;
}

int32_t write(uint8_t *data, int32_t length)
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
};

#endif
