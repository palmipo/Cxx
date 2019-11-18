OBJECTS = \
	bin/ds2482rom.o \
	bin/ds2482.o \
	bin/ds18b20.o

ONEWIRE_REP = ../../ctrl/raspberry/1wire
I2C_REP = ../../ctrl/raspberry/i2c
CC = g++
MAKE = make
INCLUDE = -I../.. -Isrc -I../../ctrl/interface -I$(ONEWIRE_REP)/src -I$(I2C_REP)/src
LIBS = -L. -lonewiredevice -lonewire -lraspii2c

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libonewiredevice.so test_ds2482

clean:
	rm -f bin/*.o libonewiredevice.so libonewire.so libraspii2c.so test_ds2482

test_ds2482: bin/test_ds2482.o libonewiredevice.so libonewire.so libraspii2c.so
	$(CC) $< -o $@ $(LDFLAGS)

bin/test_ds2482.o: test/test_ds2482.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libraspii2c.so:
	$(MAKE) -C $(I2C_REP) $@
	ln -s $(I2C_REP)/$@

libonewire.so:
	$(MAKE) -C $(ONEWIRE_REP) $@
	ln -s $(ONEWIRE_REP)/$@

libonewiredevice.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
