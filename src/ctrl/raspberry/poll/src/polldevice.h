#ifndef POLL_DEVICE_H
#define POLL_DEVICE_H

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_POLL_FACTORY_DLL
#define POLL_FACTORY_DLL __declspec(dllexport)
#else
#define POLL_FACTORY_DLL __declspec(dllimport)
#endif
#else
#define POLL_FACTORY_DLL
#endif

#include <cstdint>

class POLL_FACTORY_DLL PollDevice
{
	public:
		PollDevice();
		PollDevice(int32_t);

		virtual int32_t actionIn() = 0;
		virtual int32_t actionOut() = 0;
		virtual int32_t actionError() = 0;

		virtual int32_t write(uint8_t *, int32_t) = 0;
		virtual int32_t read(uint8_t *, int32_t) = 0;

		virtual int32_t handler();

		bool operator==(const PollDevice &) const;

	protected:
		int32_t _handler;
};

#endif
