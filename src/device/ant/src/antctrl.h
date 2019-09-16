#ifndef ANT_CTRL_H
#define ANT_CTRL_H

#include "antmaster.h"

namespace ANT
{
	class Ant;
	class Ctrl : public Master
	{
		public:
			Ctrl(uint8_t, Ant *);
			virtual ~Ctrl();
			
			virtual void sendAudioUpdateData(uint8_t, uint16_t, uint16_t, uint8_t, uint8_t);
			virtual void sendControlDeviceAvailability(uint8_t, uint8_t);
			virtual void sendTextData(int8_t *, int32_t);
			virtual void sendVideoUpdateData(uint8_t, uint16_t, uint16_t, uint8_t, uint8_t);
			virtual void sendAvailableText(int8_t *, int32_t);
			virtual void sendAudioVideoCommand(uint8_t, uint16_t, uint16_t, uint8_t, uint8_t);

			static void rfEventCallback(uint8_t, uint8_t, void *);
	};
}

#endif /* ANT_CTRL_H */
