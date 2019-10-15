#ifndef TOWER_DEVICE_H
#define TOWER_DEVICE_H

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
#include <string>

class PollDevice;
class POLL_FACTORY_DLL TowerDevice
{
	public:
		TowerDevice(PollDevice *);

		virtual int32_t actionIn(uint8_t *, int32_t) = 0;
		virtual int32_t actionOut(uint8_t *, int32_t) = 0;
		virtual int32_t actionError(uint8_t *, int32_t) = 0;

		virtual int32_t handler();

	protected:
		PollDevice * _device;
};

#endif
