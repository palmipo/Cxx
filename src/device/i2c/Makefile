OBJECTS = \
	bin/at24c32.o \
	bin/ds1307.o \
	bin/ds1621.o \
	bin/is31fl3731.o \
	bin/mcp23017.o \
	bin/mpu9255.o \
	bin/mpu9255magneto.o \
	bin/nunchuk.o \
	bin/pca9685.o \
	bin/pca9685led.o \
	bin/pcf8574a.o \
	bin/pcf8574at.o \
	bin/pcf8583.o \
	bin/pcf8593.o \
	bin/saa1064.o \
	bin/tca9548a.o \
	bin/tcs34725.o \
	bin/tda8440.o

	#bin/bmp280.o \

POLL_PWD = ../../ctrl/raspberry/factory
I2C_PWD = ../../ctrl/raspberry/i2c
USBI2C_PWD = ../../ctrl/usb_i2c
RS232_PWD = ../../ctrl/raspberry/rs232
LOG_PWD = ../../ctrl/raspberry/log
GPIO_PWD = ../../ctrl/raspberry/gpio
CC = g++
MAKE = make
INCLUDE = -I../../ctrl/interface -I../../ctrl/raspberry/factory/src -Isrc -I$(POLL_PWD)/src -I$(I2C_PWD)/src -I$(USBI2C_PWD)/src -I$(RS232_PWD)/src -I$(LOG_PWD)/src -I$(GPIO_PWD)/src
LIBS = -L. -llog -li2cdevice -lgpio -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libi2cdevice.so

#
#
clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	$(MAKE) -C $(USBI2C_PWD) $@
	$(MAKE) -C $(I2C_PWD) $@
	$(MAKE) -C $(GPIO_PWD) $@
	rm -f bin/*.o *.so test_mcp23017 raspi_nunchuk test_nunchuk test_ds1621 test_ds1307 raspi_mcp23017 test_pca9685 test_saa1064 ph_hd

#
#
ph_hd: bin/ph_hd.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libraspii2c.so
	$(MAKE) libgpio.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

bin/ph_hd.o: test/ph_hd.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_saa1064: bin/test_saa1064.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libusbi2c.so
	$(MAKE) librs232.so
	$(CC) -DUSB_I2C -o $@ $< $(LDFLAGS) -lusbi2c -lrs232

bin/test_saa1064.o: test/test_saa1064.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_nunchuk: bin/test_nunchuk.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libraspii2c.so
	$(CC) -DUSB_I2C -o $@ $< $(LDFLAGS) -lraspii2c

bin/test_nunchuk.o: test/test_nunchuk.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_mcp23017: bin/test_mcp23017.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

bin/test_mcp23017.o: test/test_mcp23017.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_pca9685: bin/test_pca9685.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

bin/test_pca9685.o: test/test_pca9685.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_ds1307: bin/test_ds1307.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

bin/test_ds1307.o: test/test_ds1307.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_ds1621: bin/test_ds1621.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

bin/test_ds1621.o: test/test_ds1621.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
libraspii2c.so:
	$(MAKE) -C $(I2C_PWD) $@
	ln -s $(I2C_PWD)/$@

#
#
libgpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

#
#
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

#
#
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

#
#
librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

#
#
libusbi2c.so:
	$(MAKE) -C $(USBI2C_PWD) $@
	ln -s $(USBI2C_PWD)/$@

#
#
libi2cdevice.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
