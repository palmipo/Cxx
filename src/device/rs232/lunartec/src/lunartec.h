#ifndef __LUNARTEC_H__
#define __LUNARTEC_H__

#include <string>
#include "batratypes.h"

class RS232;
class Lunartec
{
public:
	Lunartec(s32, RS232 *);
	~Lunartec();

	void set_time();
	void send(const std::string & texte, s8 page = 'B', s8 speed = 'C');

protected:
	void write(const std::string &);
	u8 check_sum(const std::string &);

private:
	RS232 * _usart;
	s32 _id;
};

#endif
