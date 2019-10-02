OBJECTS = \
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
LIBS = -L. -lsim900 -lrs232 -lada772 -li2cdevice -lraspii2c

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS) -llog4cxx

all: send_sms

clean:
	rm bin/*.o libsim900.so librs232.so libada772.so libi2cdevice.so libraspii2c.so send_sms

send_sms: bin/send_sms.o libsim900.so librs232.so libada772.so libi2cdevice.so libraspii2c.so
	$(CC) $< -o $@ $(LDFLAGS)
	
bin/send_sms.o: test/send_sms.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libsim900.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

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
