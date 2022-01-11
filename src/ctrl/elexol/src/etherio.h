#ifndef ETHERIO_H
#define ETHERIO_H

#include <cstdint>

namespace Socket
{
	class SocketUdp;
}
class PollDevice;
class EtherIO
{
	public:
		EtherIO(Socket::SocketUdp *);
		virtual ~EtherIO();

		virtual uint8_t getDirection(uint8_t, void (*_clb_direction)(uint8_t, uint8_t) = 0);
		virtual void setDirection(uint8_t, uint8_t);

		virtual uint8_t getPullup(uint8_t, void (*_clb_pullup)(uint8_t, uint8_t) = 0);
		virtual void setPullup(uint8_t, uint8_t);

		virtual uint8_t getThreshold(uint8_t, void (*_clb_threshold)(uint8_t, uint8_t) = 0);
		virtual void setThreshold(uint8_t, uint8_t);

		virtual uint8_t getSchmitt(uint8_t, void (*_clb_schmitt_trigger)(uint8_t, uint8_t) = 0);
		virtual void setSchmitt(uint8_t, uint8_t);

		virtual uint8_t get(uint8_t, void (*_clb_get)(uint8_t, uint8_t) = 0);
		virtual void set(uint8_t, uint8_t);

		virtual void identifyUnit(void (*_clb_io24)(uint8_t*, uint8_t*));
		virtual void sendHostData(void (*_clb_host_data)(uint32_t, uint8_t*, uint8_t*, uint16_t));
		virtual void resetModule();
		
		void setIpFixe(uint8_t *);
		void setPresetPort(uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *);
		void setAutoScan(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, uint8_t *, uint8_t *, uint16_t);

		void decode(uint8_t *, int32_t);

	protected:
		virtual void readEEPROM(uint8_t, uint8_t *, uint8_t *);
		virtual void writeEEPROM(uint8_t, uint8_t, uint8_t);
		virtual void eraseEEPROM(uint8_t);
		virtual void writeEnableEEPROM();
		virtual void writeDisableEEPROM();

	protected:
		Socket::SocketUdp * _socket;

		uint8_t _control_bit1, _control_bit2;
		void (*_clb_get)(uint8_t, uint8_t);
		void (*_clb_direction)(uint8_t, uint8_t);
		void (*_clb_pullup)(uint8_t, uint8_t);
		void (*_clb_threshold)(uint8_t, uint8_t);
		void (*_clb_schmitt_trigger)(uint8_t, uint8_t);
		void (*_clb_echo)(uint8_t);
		void (*_clb_io24)(uint8_t*, uint8_t*);
		void (*_clb_host_data)(uint32_t, uint8_t*, uint8_t*, uint16_t);
};

#endif /* ETERHIO_H */

