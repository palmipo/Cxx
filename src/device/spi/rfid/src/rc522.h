#ifndef RC522_H
#define RC522_H

class SPI;
namespace SPI
{
	class RC522
	{
		public:
			RC522(SPI *);
			virtual ~RC522();
		
			virtual void test();
			virtual void reset();

		protected:
			virtual u8 readAddress(u8);
			virtual u8 writeAddress(u8);

			virtual u8 writeRegister(u8, u8*, u8*, s32);
			virtual u8 readRegister(u8, u8*, s32);
		protected:
			SPI * _spi;
	};
}

#endif
