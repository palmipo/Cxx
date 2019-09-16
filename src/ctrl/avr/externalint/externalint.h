#ifndef __EXTERNALINT_H__
#define __EXTERNALINT_H__

class ExternalInt
{
public:
	ExternalInt();
	~ExternalInt();

	void set_irq0(unsigned char irq, void (*callback)());
	void set_irq1(unsigned char irq, void (*callback)());
	void set_irq2(unsigned char irq, void (*callback)());

	void unset_irq0();
	void unset_irq1();
	void unset_irq2();
};

#endif
