#ifndef SIM900_H_
#define SIM900_H_

#include "rs232factory.h"
#include <sstream>
#include <cstdint>

//~ 115200-8-N-1
class SIM900 : public RS232Factory
{
	public:
		SIM900(const std::string & device);
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
		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

	protected:
		RS232* _serial;
		//~ int8_t _stream[200];
		//~ int32_t _stream_length;
		//~ std::string _texte_sms;
};

#endif /* SIM900_H_ */

