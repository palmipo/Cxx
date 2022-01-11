#ifndef KS0066_GPIO_H
#define KS0066_GPIO_H

#include "ks0066_io.h

class KS0066_gpio : public KS0066_io
{
	public:
		KS0066_gpio(const std::string & dev_name, uint32_t en, uint32_t rs, uint32_t r_w_, uint32_t db7, uint32_t db6, uint32_t db5, uint32_t db4, uint32_t db3, uint32_t db2, uint32_t db1, uint32_t db0);
		virtual ~KS0066_gpio();

		virtual void set_register_select(uint8_t);
		virtual void set_read_write_(uint8_t);
		virtual void set_enable(uint8_t);
		virtual uint8_t get_data();
		virtual void set_data(uint8_t);
};

#endif
