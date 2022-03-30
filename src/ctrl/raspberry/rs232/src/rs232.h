#ifndef RS232_H
#define RS232_H

#include "polldevice.h"
#include <termios.h>
#include <string>

#if defined __MINGW64__ || __MINGW32__ || defined __CYGWIN__
#ifdef MAKE_RS232_DLL
#define RS232_DLL __declspec(dllexport)
#else
#define RS232_DLL __declspec(dllimport)
#endif
#else
#define RS232_DLL
#endif

class RS232_DLL RS232 : public PollDevice
{
	public :
		RS232(const std::string &);
		virtual ~RS232();

		virtual void setConfig(speed_t, int32_t, int32_t, int32_t, int32_t = 0);

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);
		virtual int32_t recvUntilEnd(uint8_t *, int32_t);

		virtual void setInterCharacterTimer(int32_t);
		virtual int32_t getInterCharacterTimer();

		virtual void setBlockingReadUntilCharacterArrives(int32_t);
		virtual int32_t getBlockingReadUntilCharacterArrives();

	protected :
		struct termios _oldios, _newios;
};

#endif /* RS232_H */
