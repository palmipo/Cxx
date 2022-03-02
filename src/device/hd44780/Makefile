BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hd44780.o

UTIL_REP= ../../util
INTERFACE_REP= ../../ctrl/interface
LOG_REP= ../../ctrl/raspberry/log
POLL_REP= ../../ctrl/raspberry/poll
I2C_REP = ../../ctrl/raspberry/i2c
GPIO_REP = ../../ctrl/raspberry/gpio
USBI2C_REP = ../../ctrl/usb_i2c
RS232_REP = ../../ctrl/raspberry/rs232
I2CDEV_REP = ../i2c
AR = ar
CC = g++
MAKE = make
INCLUDE = -I$(INTERFACE_REP)/src -I$(UTIL_REP)/src -Isrc -I$(I2C_REP)/src -I$(USBI2C_REP)/src -I$(RS232_REP)/src -I$(I2CDEV_REP)/src -I$(GPIO_REP)/src -I$(POLL_REP)/src -I$(LOG_REP)/src
LIBS =

CFLAGS = -g $(INCLUDE) -DRASPI
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(LOG_REP) $@
	$(MAKE) -C $(RS232_REP) $@
	$(MAKE) -C $(USBI2C_REP) $@
	$(MAKE) -C $(I2C_REP) $@
	$(MAKE) -C $(I2CDEV_REP) $@
	rm -f $(BIN_PWD)/*.o *.so test_2004 test_hd44780

test_hd44780: $(BIN_PWD)/test_hd44780.o libada772.so libhd44780.so libraspigpio.so libi2cdevice.so libraspii2c.so libpoll.so libutil.so liblog.so
	$(CC) $< -o $@ $(LDFLAGS) -L. -lraspii2c -li2cdevice -lpoll -lraspigpio -lhd44780 -lada772 -lutil -llog

$(BIN_PWD)/test_hd44780.o: test/test_hd44780.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

test_2004: $(BIN_PWD)/test_2004.o liblcd2004.so libhd44780.so libi2cdevice.so libraspii2c.so liblog.so
	$(CC) $< -o $@ $(LDFLAGS) -L. -lraspii2c -li2cdevice -lhd44780 -llcd2004 -llog

$(BIN_PWD)/test_2004.o: test/test_2004.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libutil.so:
	$(MAKE) -C $(UTIL_REP) $@
	ln -s $(UTIL_REP)/$@

liblog.so:
	$(MAKE) -C $(LOG_REP) $@
	ln -s $(LOG_REP)/$@

libpoll.so:
	$(MAKE) -C $(POLL_REP) $@
	ln -s $(POLL_REP)/$@

librs232.so:
	$(MAKE) -C $(RS232_REP) $@
	ln -s $(RS232_REP)/$@

libusbi2c.so:
	$(MAKE) -C $(USBI2C_REP) $@
	ln -s $(USBI2C_REP)/$@

libraspigpio.so:
	$(MAKE) -C $(GPIO_REP) $@
	ln -s $(GPIO_REP)/$@

libraspii2c.so:
	$(MAKE) -C $(I2C_REP) $@
	ln -s $(I2C_REP)/$@

libi2cdevice.so:
	$(MAKE) -C $(I2CDEV_REP) $@
	ln -s ../i2c/$@

libhd44780.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libhd44780.a: $(OBJECTS)
	$(AR) r $@ $^

libada772.so: $(BIN_PWD)/ada772.o
	$(CC) -shared $^ -o $@

liblcd2004.so: $(BIN_PWD)/lcd2004.o
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -fPIC -o $@
