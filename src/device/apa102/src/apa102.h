#ifndef APA102_H
#define APA102_H

class APA102
{
APA102(PIA *);
virtual void write(uint8_t *, int32_t);
};

#endif /* APA102 */
