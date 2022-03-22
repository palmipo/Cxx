#ifndef SIM900_H_
#define SIM900_H_

#include <string>
#include <cstdint>

//~ 115200-8-N-1
class RS232;
class SIM900
{
	public:
		SIM900(RS232 *);
		virtual ~SIM900();

		virtual void atz();

		virtual void send_call(const std::string &);

		virtual void init_sms();
		virtual void list_sms();
		virtual void write_sms(const std::string &, const std::string &);
		virtual void read_sms(int32_t);
		virtual void delete_sms(int32_t);

		virtual void get_clock();

	protected:
		virtual int32_t send_cmd(const std::string &);

	protected:
		RS232 * _serial;
};

#endif /* SIM900_H_ */

