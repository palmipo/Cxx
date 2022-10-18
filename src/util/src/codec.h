#ifndef CODEC_H
#define CODEC_H

#include <cstdint>

class Codec
{
	public:
		Codec();
		virtual ~Codec();
	
		void encoder_decoder(uint8_t*, int32_t, uint8_t*, int32_t, int32_t, int32_t=0, int32_t=0);
};

#endif /* CODEC_H */
