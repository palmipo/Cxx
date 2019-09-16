#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H

#include <cstdint>
#include <vector>

class CanBuffer
{
	public:
		CanBuffer();
		virtual ~CanBuffer();

		uint16_t node_id;
		std::vector < uint8_t > data;
};

#endif /* CAN_BUFFER_H */
