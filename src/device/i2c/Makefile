BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/phat_enviro.o \
	$(BIN_PWD)/at24c32.o \
	$(BIN_PWD)/bmp280.o \
	$(BIN_PWD)/bme280.o \
	$(BIN_PWD)/ds1307.o \
	$(BIN_PWD)/ds1621.o \
	$(BIN_PWD)/is31fl3731.o \
	$(BIN_PWD)/mcp23017.o \
	$(BIN_PWD)/mpu9255.o \
	$(BIN_PWD)/mpu9255magneto.o \
	$(BIN_PWD)/nunchuk.o \
	$(BIN_PWD)/pca9685.o \
	$(BIN_PWD)/pca9685led.o \
	$(BIN_PWD)/pcf8574a.o \
	$(BIN_PWD)/pcf8574at.o \
	$(BIN_PWD)/pcf8583.o \
	$(BIN_PWD)/pcf8593.o \
	$(BIN_PWD)/saa1064.o \
	$(BIN_PWD)/tca9548a.o \
	$(BIN_PWD)/tcs34725.o \
	$(BIN_PWD)/tda8440.o


UTIL_PWD = ../../util
CTRL_PWD = ../../ctrl
USBI2C_PWD = $(CTRL_PWD)/usb_i2c
RASPI_PWD = $(CTRL_PWD)/raspberry
POLL_PWD = $(RASPI_PWD)/poll
INTERFACE_PWD = $(CTRL_PWD)/interface
I2C_PWD = $(RASPI_PWD)/i2c
RS232_PWD = $(RASPI_PWD)/rs232
LOG_PWD = $(RASPI_PWD)/log
GPIO_PWD = $(RASPI_PWD)/gpio
PIA_PWD = ../pia
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_PWD)/src -I$(INTERFACE_PWD)/src -Isrc -I$(PIA_PWD)/src -I$(POLL_PWD)/src -I$(I2C_PWD)/src -I$(USBI2C_PWD)/src -I$(RS232_PWD)/src -I$(LOG_PWD)/src -I$(GPIO_PWD)/src
LIBS = -L. -lutil -llog -li2cdevice -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libi2cdevice.so

#
#
clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(UTIL_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	$(MAKE) -C $(USBI2C_PWD) $@
	$(MAKE) -C $(I2C_PWD) $@
	$(MAKE) -C $(GPIO_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so test_mcp23017 raspi_nunchuk test_nunchuk test_ds1621 test_ds1307 raspi_mcp23017 test_pca9685 test_saa1064 ph_hd

#
#
bmp280: $(BIN_PWD)/test_bmp280.o liblog.so libutil.so libpoll.so libi2cdevice.so libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c -llog -lutil

$(BIN_PWD)/test_bmp280.o: test/test_bmp280.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

ph_hd: $(BIN_PWD)/ph_hd.o liblog.so libutil.so libpoll.so libi2cdevice.so libraspii2c.so libraspigpio.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c -lraspigpio

$(BIN_PWD)/ph_hd.o: test/ph_hd.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
ph_enviro: $(BIN_PWD)/test_phat_enviro.o liblog.so libutil.so libpoll.so libi2cdevice.so libraspii2c.so libraspigpio.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

$(BIN_PWD)/test_phat_enviro.o: test/test_phat_enviro.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_saa1064: $(BIN_PWD)/test_saa1064.o liblog.so libpoll.so libi2cdevice.so libusbi2c.so librs232.so
	$(CC) -DUSB_I2C -o $@ $< $(LDFLAGS) -lusbi2c -lrs232

$(BIN_PWD)/test_saa1064.o: test/test_saa1064.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_nunchuk: $(BIN_PWD)/test_nunchuk.o liblog.so libpoll.so libi2cdevice.so libraspii2c.so
	$(CC) -DUSB_I2C -o $@ $< $(LDFLAGS) -lraspii2c

$(BIN_PWD)/test_nunchuk.o: test/test_nunchuk.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_mcp23017: $(BIN_PWD)/test_mcp23017.o liblog.so libpoll.so libi2cdevice.so libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

$(BIN_PWD)/test_mcp23017.o: test/test_mcp23017.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_pca9685: $(BIN_PWD)/test_pca9685.o liblog.so libpoll.so libi2cdevice.so libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

$(BIN_PWD)/test_pca9685.o: test/test_pca9685.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_ds1307: $(BIN_PWD)/test_ds1307.o liblog.so libpoll.so libutil.so libi2cdevice.so libusbi2c.so librs232.so
	$(CC) -o $@ $< $(LDFLAGS) -lrs232 -lusbi2c

$(BIN_PWD)/test_ds1307.o: test/test_ds1307.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
test_ds1621: $(BIN_PWD)/test_ds1621.o liblog.so libpoll.so libi2cdevice.so libraspii2c.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspii2c

$(BIN_PWD)/test_ds1621.o: test/test_ds1621.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
libraspii2c.so:
	$(MAKE) -C $(I2C_PWD) $@
	ln -s $(I2C_PWD)/$@

#
#
libraspigpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

#
#
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

#
#
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

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
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI
