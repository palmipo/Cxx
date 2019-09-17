OBJECTS = \
	bin/usb_i2c.o

RS232_PWD = ../raspberry/rs232
CC = g++
INCLUDE = -I../.. -I../interface -I../raspberry/factory/src -Isrc -I$(RS232_PWD)/src
LIBS = -L. -lusbi2c -lrs232

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libusbi2c.so

clean:
	rm -f bin/*.o libusbi2c.so librs232.so usbi2c

libusbi2c.so: $(OBJECTS)
	mkdir bin
	$(MAKE) librs232.so
	$(CC) -shared $^ -o $@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

usbi2c: bin/main.o
	$(MAKE) librs232.so
	$(MAKE) libusbi2c.so
	$(CC) $< -o $@ $(LDFLAGS)

bin/main.o: test/main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
