#include "raspii2c.h"
#include "i2cexception.h"
#include "log.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
// #include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <iomanip>

//~ Full interface description
//~ ==========================

//~ #define I2C_M_TEN               0x0010  /* this is a ten bit chip address */
//~ #define I2C_M_RD                0x0001  /* read data, from slave to master */
//~ #define I2C_M_NOSTART           0x4000  /* if I2C_FUNC_PROTOCOL_MANGLING */
//~ #define I2C_M_REV_DIR_ADDR      0x2000  /* if I2C_FUNC_PROTOCOL_MANGLING */
//~ #define I2C_M_IGNORE_NAK        0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
//~ #define I2C_M_NO_RD_ACK         0x0800  /* if I2C_FUNC_PROTOCOL_MANGLING */
//~ #define I2C_M_RECV_LEN          0x0400  /* length will be first received byte */
//~ struct i2c_msg {
        //~ __u16 addr;     /* slave address                        */
        //~ __u16 flags;
        //~ __u16 len;              /* msg length                           */
        //~ __u8 *buf;              /* pointer to msg data                  */
//~ };

//~ The following IOCTLs are defined:

//~ ioctl(file, I2C_SLAVE, long addr)
  //~ Change slave address. The address is passed in the 7 lower bits of the
  //~ argument (except for 10 bit addresses, passed in the 10 lower bits in this
  //~ case).

//~ ioctl(file, I2C_TENBIT, long select)
  //~ Selects ten bit addresses if select not equals 0, selects normal 7 bit
  //~ addresses if select equals 0. Default 0.  This request is only valid
  //~ if the adapter has I2C_FUNC_10BIT_ADDR.

//~ ioctl(file, I2C_PEC, long select)
  //~ Selects SMBus PEC (packet error checking) generation and verification
  //~ if select not equals 0, disables if select equals 0. Default 0.
  //~ Used only for SMBus transactions.  This request only has an effect if the
  //~ the adapter has I2C_FUNC_SMBUS_PEC; it is still safe if not, it just
  //~ doesn't have any effect.

//~ ioctl(file, I2C_FUNCS, unsigned long *funcs)
  //~ Gets the adapter functionality and puts it in *funcs.

//~ ioctl(file, I2C_RDWR, struct i2c_rdwr_ioctl_data *msgset)
  //~ Do combined read/write transaction without stop in between.
  //~ Only valid if the adapter has I2C_FUNC_I2C.  The argument is
  //~ a pointer to a

  //~ struct i2c_rdwr_ioctl_data {
      //~ struct i2c_msg *msgs;  /* ptr to array of simple messages */
      //~ int nmsgs;             /* number of messages to exchange */
  //~ }

  //~ The msgs[] themselves contain further pointers into data buffers.
  //~ The function will write or read data to or from that buffers depending
  //~ on whether the I2C_M_RD flag is set in a particular message or not.
  //~ The slave address and whether to use ten bit address mode has to be
  //~ set in each message, overriding the values set with the above ioctl's.

//~ ioctl(file, I2C_SMBUS, struct i2c_smbus_ioctl_data *args)
  //~ Not meant to be called  directly; instead, use the access functions
  //~ below.

//~ You can do plain i2c transactions by using read(2) and write(2) calls.
//~ You do not need to pass the address byte; instead, set it through
//~ ioctl I2C_SLAVE before you try to access the device.


RaspiI2C::RaspiI2C(const char * device)
{
	if ((_fd = open(device, O_RDWR)) < 0)
		throw I2CException("I2C::I2C()");

	uint32_t val = 0;
	if (ioctl(_fd, I2C_TENBIT, val) < 0)
		throw I2CException("I2C::I2C_TENBIT()");

	uint32_t fct = 0;
	if (ioctl(_fd, I2C_FUNCS, &fct) < 0)
		throw I2CException("I2C::I2C_FUNCS()");
	
	if ((fct & I2C_FUNC_I2C) != I2C_FUNC_I2C)
		throw I2CException("I2C::I2C_FUNC_I2C()");
}

RaspiI2C::~RaspiI2C()
{
	close(_fd);
}

// void RaspiI2C::setOwnAddress(uint8_t own_address)
// {
	// if (ioctl(_fd, I2C_SLAVE, (long)own_address) < 0)
		// throw I2CException("I2C::setOwnAddress()");
// }

void RaspiI2C::set(uint8_t addr, uint8_t* buf, int32_t len)
{
	std::stringstream ss;
	ss << "I2C::write() ";
	for (int32_t i=0; i<len; ++i)
	{
		ss << std::hex << (int)buf[i] << " ";
	}
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	struct i2c_rdwr_ioctl_data msg;
	msg.msgs = new i2c_msg[1];
	msg.nmsgs = 1;

	msg.msgs[0].addr = addr;
	msg.msgs[0].flags = 0;
	msg.msgs[0].len = len;
	msg.msgs[0].buf = buf;

	if (ioctl(_fd, I2C_RDWR, &msg) < 0)
		throw I2CException("I2C::write()");
	
	delete[] msg.msgs;
}

void RaspiI2C::get(uint8_t addr, uint8_t* buf, int32_t len)
{
	struct i2c_rdwr_ioctl_data msg;
	msg.msgs = new i2c_msg[1];
	msg.nmsgs = 1;

	msg.msgs[0].addr = addr;
	msg.msgs[0].flags = I2C_M_RD;
	msg.msgs[0].len = len;
	msg.msgs[0].buf = buf;

	if (ioctl(_fd, I2C_RDWR, &msg) < 0)
		throw I2CException("I2C::read()");
	
	std::stringstream ss;
	ss << "I2C::read() ";
	for (int32_t i=0; i<len; ++i)
	{
		ss << std::hex << (int)buf[i] << " ";
	}
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	delete[] msg.msgs;
}

void RaspiI2C::transfert(uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len)
{

	struct i2c_rdwr_ioctl_data msg;
	msg.msgs = new i2c_msg[2];
	msg.nmsgs = 2;

	// buffer ecriture
	msg.msgs[0].addr = addr;
	msg.msgs[0].flags = 0;
	msg.msgs[0].len = cmd_len;
	msg.msgs[0].buf = cmd;
	
	// buffer lecture
	msg.msgs[1].addr = addr;
	msg.msgs[1].flags = I2C_M_RD;
	msg.msgs[1].len = buf_len;
	msg.msgs[1].buf = buf;
	memset(msg.msgs[1].buf, 0, msg.msgs[1].len);

	if (ioctl(_fd, I2C_RDWR, &msg) < 0)
		throw I2CException("I2C::I2C_RDWR()");
	
	std::stringstream ss;
	ss << "I2C::transfert() emission : ";
	for (int32_t i=0; i<cmd_len; ++i)
	{
		ss << std::hex << (int)cmd[i] << " ";
	}
	ss << "; reception : ";
	for (int32_t i=0; i<buf_len; ++i)
	{
		ss << std::hex << (int)buf[i] << " ";
	}
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	delete[] msg.msgs;
}
