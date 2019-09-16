#ifndef HC_SR04_H
#define HC_SR04_H

class HC_SR04
{
	public:
		HC_SR04(Gpio * out, Gpio * in);
		int32_t distance();
};

#endif /* HC_SR04_H */
