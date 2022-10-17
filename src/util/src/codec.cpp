#include "codec.h"

Codec::Codec()
{}

Codec::~Codec()
{}

void Codec::encoder_decoder(uint8_t* dst, int32_t dst_start_bit, uint8_t* src, int32_t src_start_bit, int32_t size, int32_t inversion_octet)
{
	int32_t i_octet = src_start_bit >> 3;
	int32_t i_bit = src_start_bit - (i_octet << 3);
	int32_t j_octet = dst_start_bit >> 3;
	int32_t j_bit = dst_start_bit - (j_octet << 3);

	for (int32_t i=0; i<size; ++i)
	{
		dst[j_octet] |= ((src[i_octet] & (1 << i_bit)) >> i_bit) << ((inversion_octet) ? (7 - j_bit) : j_bit);
		i_bit += 1;
		j_bit += 1;
		if (i_bit > 7) { i_bit = 0; i_octet += 1; }
		if (j_bit > 7) { j_bit = 0; j_octet += 1; }
	}
}
