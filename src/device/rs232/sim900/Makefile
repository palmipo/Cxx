OBJECTS = \
	bin/sim900buffer.o \
	bin/sim900.o

POLL_PWD = ../../../ctrl/raspberry/factory
LOG_PWD = ../../../ctrl/raspberry/log
RS232_PWD = ../../../ctrl/raspberry/rs232
I2C_PWD = ../../../ctrl/raspberry/i2c
I2C_DEVICE_PWD = ../../i2c
HD44780_PWD = ../../hd44780
CC = g++
MAKE = make
INCLUDE = -I$(POLL_PWD)/src -I$(LOG_PWD)/src -Isrc -I$(RS232_PWD)/src/ -I$(I2C_PWD)/src/ -I$(I2C_DEVICE_PWD)/src/ -I$(HD44780_PWD)/src/
LIBS = -L. -lrs232 -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: send_sms

clean:
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	$(MAKE) -C $(I2C_PWD) $@
	$(MAKE) -C $(I2C_DEVICE_PWD) $@
	$(MAKE) -C $(HD44780_PWD) $@
	rm bin/*.o *.dll *.so send_sms

send_sms: bin/send_sms.o
	$(MAKE) libpoll.so
	$(MAKE) liblog.so
	$(MAKE) libsim900.so
	$(MAKE)	librs232.so
	$(CC) $< -o $@ $(LDFLAGS) -lsim900 -lpthread

bin/send_sms.o: test/send_sms.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libsim900.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libraspii2c.so:
	$(MAKE) -C $(I2C_PWD) $@
	ln -s $(I2C_PWD)/$@

libi2cdevice.so:
	$(MAKE) -C $(I2C_DEVICE_PWD) $@
	ln -s $(I2C_DEVICE_PWD)/$@

libada772.so:
	$(MAKE) -C $(HD44780_PWD) $@
	ln -s $(HD44780_PWD)/$@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
