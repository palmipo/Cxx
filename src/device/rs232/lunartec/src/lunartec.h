#ifndef __LUNARTEC_H__
#define __LUNARTEC_H__

#include <string>
#include <cstdint>

class RS232;
class Lunartec
{
public:
	Lunartec(int32_t, RS232 *);
	~Lunartec();

	void set_time();
	void send(const std::string & texte, int8_t page = 'B', int8_t speed = 'C');

protected:
	void write(const std::string &);
	uint8_t check_sum(const std::string &);

private:
	RS232 * _usart;
	int32_t _id;
};

#endif
