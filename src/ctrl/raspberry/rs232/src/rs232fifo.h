#ifndef RS232_FIFO_H
#define RS232_FIFO_H

#include "rs232.h"
#include "rs232buffer.h"
#include <queue>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_RS232_DLL
#define RS232_DLL __declspec(dllexport)
#else
#define RS232_DLL __declspec(dllimport)
#endif
#else
#define RS232_DLL
#endif

class RS232_DLL RS232Fifo : public RS232
{
	public :
		RS232Fifo(const std::string &);
		virtual ~RS232Fifo();

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t, int32_t = 10, int32_t = 1000);
		virtual int32_t actionIn();
		virtual int32_t actionOut();

	protected:
		std::queue < RS232Buffer * > _fifo_in;
		std::queue < RS232Buffer * > _fifo_out;
};

#endif /* RS232_FIFO_H */
