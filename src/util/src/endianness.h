#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include <cstdint>

template <class T>
class Endianness
{
	public:
		Endianness()
		: _little_endian(false)
		{
			int32_t i = 1;
			uint8_t * c = (uint8_t*)&i;
			if (c[0] == i)
			{
				_little_endian = true;
			}
		}

		T toLittleEndian(T i)
		{
			if (_little_endian)
			{
				return i;
			}
			else
			{
				return inversion(i);
			}
		}

		T toBigEndian(T i)
		{
			if (_little_endian)
			{
				return inversion(i);
			}
			else
			{
				return i;
			}
		}

	protected:
		T inversion(T i)
		{
			T k;
			uint8_t * c = (uint8_t*)&i;
			uint8_t * d = (uint8_t*)&k;
			int32_t l = sizeof(i);
			for (int32_t j=0; j<l; ++j)
			{
				d[j] = c[l-j-1];
			}
			return k;
		}

	protected:
		uint8_t _little_endian;
};

#endif
