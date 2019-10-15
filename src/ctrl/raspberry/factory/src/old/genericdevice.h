#ifndef GENERIC_DEVICE_H
#define GENERIC_DEVICE_H

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_POLL_FACTORY_DLL
#define POLL_FACTORY_DLL __declspec(dllexport)
#else
#define POLL_FACTORY_DLL __declspec(dllimport)
#endif
#else
#define POLL_FACTORY_DLL
#endif

#include "towerdevice.h"
#include <queue>

class PollBuffer;
class PollDevice;
class POLL_FACTORY_DLL GenericDevice : public TowerDevice
{
	public:
		GenericDevice(PollDevice *);

		virtual int32_t read(uint8_t *, int32_t, int32_t = 10, int32_t = 1000);
		virtual int32_t write(uint8_t *, int32_t);

		virtual int32_t actionIn(uint8_t *, int32_t);
		virtual int32_t actionOut(uint8_t *, int32_t);
		virtual int32_t actionError(uint8_t *, int32_t);
		
	protected:
		std::queue < PollBuffer * > _fifo;
};

#endif
