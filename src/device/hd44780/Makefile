BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hd44780.o

UTIL_REP= ../../util
INTERFACE_REP= ../../ctrl/interface
RASPI_REP= ../../ctrl/raspberry
POLL_REP= $(RASPI_REP)/poll
I2C_REP = $(RASPI_REP)/i2c
GPIO_REP = $(RASPI_REP)/gpio
I2CDEV_REP = ../i2c
AR = ar
CC = g++
MAKE = make
INCLUDE = -I$(INTERFACE_REP)/src -I$(UTIL_REP)/src -Isrc -I$(I2C_REP)/src -I$(I2CDEV_REP)/src -I$(GPIO_REP)/src -I$(POLL_REP)/src
LIBS =

CFLAGS = -g $(INCLUDE) -DRASPI
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so test_2004 test_hd44780

test_hd44780: $(BIN_PWD)/test_hd44780.o libada772.so libhd44780.so libraspi.so libi2cdevice.so
	$(CC) $< -o $@ $(LDFLAGS) -L. -li2cdevice -lraspi -lhd44780 -lada772 -lpthread

$(BIN_PWD)/test_hd44780.o: test/test_hd44780.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

test_2004: $(BIN_PWD)/test_2004.o liblcd2004.so libhd44780.so libi2cdevice.so libraspi.so
	$(CC) $< -o $@ $(LDFLAGS) -L. -lraspi -li2cdevice -lhd44780 -llcd2004

$(BIN_PWD)/test_2004.o: test/test_2004.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libraspi.so:
	$(MAKE) -C $(RASPI_REP) $@
	ln -s $(RASPI_REP)/$@

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
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -fPIC -o $@
