#ifndef SIM900_H_
#define SIM900_H_

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_SIM900_DLL
#define SIM900_DLL __declspec(dllexport)
#else
#define SIM900_DLL __declspec(dllimport)
#endif
#else
#define SIM900_DLL
#endif

#include "rs232factory.h"
#include <sstream>
#include <cstdint>
#include <queue>

//~ 115200-8-N-1
class RS232;
class Sim900Buffer;
class SIM900 : public RS232Factory
{
	public:
		SIM900(const std::string & device);
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

		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

	protected:
		RS232* _serial;
		std::string _texte_sms;
		Sim900Buffer * _buffer;
		std::queue < Sim900Buffer * > _fifo;
};

#endif /* SIM900_H_ */

