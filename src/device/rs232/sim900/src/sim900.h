#ifndef SIM900_H_
#define SIM900_H_

#include <sstream>
#include "batratypes.h"

//~ 115200-8-N-1
class RS232;
class SIM900
{
	public:
		SIM900(RS232* serial);
		virtual ~SIM900();

		virtual void atz();

		virtual void send_call(const std::string &);

		virtual void init_sms();
		virtual void list_sms();
		virtual void send_sms(const std::string &, const std::string &);
		virtual void recv_sms(int32_t);
		virtual void delete_sms(int32_t);

		virtual void get_clock();

		static void reception_message(void *);
		virtual int32_t analyse_message(int8_t*, int32_t);

	protected:
		virtual int32_t read_uart(int8_t*, int32_t);

	protected:
		RS232* _serial;
		//~ int8_t _stream[200];
		//~ int32_t _stream_length;
		//~ std::string _texte_sms;
};

#endif /* SIM900_H_ */

