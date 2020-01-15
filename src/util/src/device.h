#ifndef DEVICE_H
#define DEVICE_H

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_UTIL_DLL
#define UTIL_DLL __declspec(dllexport)
#else
#define UTIL_DLL __declspec(dllimport)
#endif
#else
#define UTIL_DLL
#endif

#include <cstdint>

class UTIL_DLL Device
{
	public:
		Device();
		Device(int32_t);

		virtual int32_t actionIn() = 0;
		virtual int32_t actionOut() = 0;
		virtual int32_t actionError() = 0;

		virtual int32_t handler();

		bool operator==(const Device &) const;

	protected:
		int32_t _handler;

	protected:
		int32_t _max_retry;
		int32_t _timeout;
};

#endif
