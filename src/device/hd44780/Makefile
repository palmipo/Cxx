OBJECTS = \
	bin/hd44780.o

I2C_REP = ../../ctrl/raspberry/i2c
GPIO_REP = ../../ctrl/raspberry/gpio
USBI2C_REP = ../../ctrl/usb_i2c
RS232_REP = ../../ctrl/raspberry/rs232
AR = ar
CC = g++
MAKE = make
INCLUDE = -I../.. -I../../ctrl/interface -Isrc -I$(I2C_REP)/src -I$(USBI2C_REP)/src -I$(RS232_REP)/src -I../i2c/src -I.. -I$(GPIO_REP)/src
LIBS =

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f bin/*.o *.so

test_hd44780: bin/test_hd44780.o libada772.so libi2cdevice.so libraspii2c.so
	$(CC) $< -o $@ $(LDFLAGS) -L. -lraspii2c -li2cdevice -lada772

bin/test_hd44780.o: test/test_hd44780.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

test_2004: bin/test_2004.o liblcd2004.so libi2cdevice.so libraspii2c.so
	$(CC) $< -o $@ $(LDFLAGS) -L. -lraspii2c -li2cdevice -llcd2004

bin/test_2004.o: test/test_2004.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

librs232.so:
	$(MAKE) -C $(RS232_REP) $@
	ln -s $(RS232_REP)/$@

libusbi2c.so:
	$(MAKE) -C $(USBI2C_REP) $@
	ln -s $(USBI2C_REP)/$@

libraspii2c.so:
	$(MAKE) -C $(I2C_REP) $@
	ln -s $(I2C_REP)/$@

libi2cdevice.so:
	$(MAKE) -C ../i2c $@
	ln -s ../i2c/$@

libhd44780.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libhd44780.a: $(OBJECTS)
	$(AR) r $@ $^

libada772.so: bin/ada772.o libhd44780.a
	$(CC) -shared $^ -o $@

liblcd2004.so: bin/lcd2004.o libhd44780.a
	$(CC) -shared $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
