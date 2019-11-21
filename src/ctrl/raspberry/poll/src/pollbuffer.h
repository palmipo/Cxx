#ifndef POLL_BUFFER_H
#define POLL_BUFFER_H

#include <cstdint>
#include <vector>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_POLL_FACTORY_DLL
#define POLL_FACTORY_DLL __declspec(dllexport)
#else
#define POLL_FACTORY_DLL __declspec(dllimport)
#endif
#else
#define POLL_FACTORY_DLL
#endif

class POLL_FACTORY_DLL PollBuffer
{
	public:
		PollBuffer();

		virtual int32_t read(uint8_t *, int32_t);
		virtual int32_t write(uint8_t *, int32_t);
	
	protected:
		std::vector < uint8_t > _buffer;
};

#endif /* POLL_BUFFER_H */
