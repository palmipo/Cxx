#include "ks0066_gpio.h

KS0066_gpio::KS0066_gpio(const std::string & dev_name, uint32_t en, uint32_t rs, uint32_t r_w_, uint32_t db7, uint32_t db6, uint32_t db5, uint32_t db4, uint32_t db3, uint32_t db2, uint32_t db1, uint32_t db0)
: KS0066_io()
{
	printf("Write value %d to GPIO at offset %d (OUTPUT mode) on chip %s\n", value, offset, dev_name);
	int32_t fd = open(dev_name.c_str(), O_RDONLY);
	if (fd < 0)
	{
		printf("Unabled to open %s: %s", dev_name, strerror(errno));
		return;
	}
	
	struct gpiohandle_request rq;
	rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
	rq.lines = 3;
	rq.lineoffsets[0] = en;
	rq.lineoffsets[1] = rs;
	rq.lineoffsets[2] = r_w_;
	int32_t ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
	if (ret == -1)
	{
		printf("Unable to line handle from ioctl : %s", strerror(errno));
		return;
	}
}

KS0066_gpio::~KS0066_gpio()
{
	close(rq.fd);
	close(fd);
}

void KS0066_gpio::set_register_select(uint8_t value)
{
	struct gpiohandle_data data;
	data.values[1] = value ? 1 : 0;
	ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	if (ret == -1)
}

void KS0066_gpio::set_read_write_(uint8_t value)
{
	struct gpiohandle_data data;
	data.values[2] = value ? 1 : 0;
	ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	if (ret == -1)
}

void KS0066_gpio::set_enable(uint8_t value)
{
	struct gpiohandle_data data;
	data.values[0] = value ? 1 : 0;
	ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	if (ret == -1)
}

uint8_t KS0066_gpio::get_data()
{
	struct gpiohandle_request rq;
	rq.flags = GPIOHANDLE_REQUEST_INPUT;
	rq.lines = 8;
	rq.lineoffsets[0] = db7;
	rq.lineoffsets[1] = db6;
	rq.lineoffsets[2] = db5;
	rq.lineoffsets[3] = db4;
	rq.lineoffsets[4] = db3;
	rq.lineoffsets[5] = db2;
	rq.lineoffsets[6] = db1;
	rq.lineoffsets[7] = db0;
	int32_t ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
	if (ret == -1)
	{
		printf("Unable to get line handle from ioctl : %s", strerror(errno));
		return;
	}

	struct gpiohandle_data data;
	ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
	if (ret == -1)
	{
		printf("Unable to get line value using ioctl : %s", strerror(errno));
	}
	else
	{
		printf("Value of GPIO at offset %d (INPUT mode) on chip %s: %d\n", offset, dev_name, data.values[0]);
	}
	close(rq.fd);
}

void KS0066_gpio::set_data(uint8_t)
{
	printf("Write value %d to GPIO at offset %d (OUTPUT mode) on chip %s\n", value, offset, dev_name);
	struct gpiohandle_request rq;
	rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
	rq.lines = 8;
	rq.lineoffsets[0] = db7;
	rq.lineoffsets[1] = db6;
	rq.lineoffsets[2] = db5;
	rq.lineoffsets[3] = db4;
	rq.lineoffsets[4] = db3;
	rq.lineoffsets[5] = db2;
	rq.lineoffsets[6] = db1;
	rq.lineoffsets[7] = db0;
	int32_t ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
	if (ret == -1)
	{
		printf("Unable to line handle from ioctl : %s", strerror(errno));
		return;
	}
	
	struct gpiohandle_data data;
	for (int32_t i=0; i<8; ++i)
	{
		data.values[i] = (value & (1<<i)) ? 1 : 0;
	}
	ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	if (ret == -1)
	{
		printf("Unable to set line value using ioctl : %s", strerror(errno));
	}
	else
	{
		usleep(2000000);
	}
	close(rq.fd);
}
