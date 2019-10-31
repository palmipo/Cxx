#include "endianness.h"
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	int8_t a = 8;
	Endianness<int8_t> aa;
	std::cout << std::hex << "0x" << (int32_t)a << " 0x" << (int32_t)aa.toBigEndian(a) << std::endl;

	int16_t b = 16;
	Endianness<int16_t> bb;
	std::cout << std::hex << "0x" << b << " 0x" << bb.toBigEndian(b) << std::endl;

	int32_t c = 32;
	Endianness<int32_t> cc;
	std::cout << std::hex << "0x" << c << " 0x" << cc.toBigEndian(c) << std::endl;

	struct st
	{
		int32_t a;
		int16_t b;
	};
	struct st d;
	d.a = 32;
	d.b = 16;
	Endianness<struct st> dd;
	std::cout << std::hex << "0x" << d.a << " 0x" << dd.toBigEndian(d).b << std::endl;

	return 0;
}
