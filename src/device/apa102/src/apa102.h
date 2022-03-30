#ifndef APA102_H
#define APA102_H

#include <cstdint>

class CtrlPIA;
class APA102
{
	APA102(CtrlPIA *);
	virtual void write(uint8_t *, int32_t);
};

#endif /* APA102 */
