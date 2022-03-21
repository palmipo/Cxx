#ifndef COLECOVISION_H
#define COLECOVISION_H

class PIA;
class ColecoVision
{
public:
	ColecoVision(PIA *, PIA *);
	virtual ~ColecoVision();

	void read();

protected:
	PIA * _out;
	PIA * _in;
};

#endif /* COLECOVISION_H */
