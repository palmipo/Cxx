#include "apa102.h"

APA102::APA102(PIA * out)
: _out(out)
{}

APA102::~APA102()
{}

// data : brillance, rouge, vert, bleu
void APA102::write(uint8_t data, int32_t length)
{
for (int32_t i=0; i<32; ++i)
{
write_bit(0);
}
for (int32_t i=0; i<length; i+=4)
{
write_octet(0xE0 | data[i]);
write_octet(data[i+1]);
write_octet(data[i+2]);
write_octet(data[i+3]);
}
for (int32_t i=0; i<32; ++i)
{
write_bit(1);
}
}
