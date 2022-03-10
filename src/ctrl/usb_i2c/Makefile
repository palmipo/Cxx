HOSTNAME = hostname
BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/usb_i2c.o

MAKE = make
MKDIR = mkdir -p
CC = g++
UTIL_PWD = ../../util
POLL_PWD = ../raspberry/poll
RS232_PWD = ../raspberry/rs232
IFACE_PWD = ../interface
INCLUDE = -I$(IFACE_PWD)/src -I$(POLL_PWD)/src -Isrc -I$(RS232_PWD)/src -I$(UTIL_PWD)/src
LIBS = -L. -lusbi2c -lrs232 -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE) -DRASPI -fPIC
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll usbi2c

usbi2c: $(BIN_PWD)/main.o
	$(MAKE) libusbi2c.so
	$(CC) $< -o $@ $(LDFLAGS)

usbi2c.exe: $(BIN_PWD)/main.o
	$(MAKE) libusbi2c.dll
	$(CC) $< -o $@ $(LDFLAGS)

$(BIN_PWD)/main.o: test/main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
##
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so:
	$(MAKE) libpoll.so
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libusbi2c.so: $(OBJECTS)
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -shared $^ -o $@

#
##
libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

librs232.dll:
	$(MAKE) libpoll.dll
	$(MAKE) -C $(RS232_PWD) $@
	cp $(RS232_PWD)/$@ .

libusbi2c.dll: $(OBJECTS)
	$(MAKE) librs232.dll
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
