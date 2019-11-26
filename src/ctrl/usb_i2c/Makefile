BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/usb_i2c.o

MAKE = make
MKDIR = mkdir -p
CC = g++
UTIL_PWD = ../../util
LOG_PWD = ../raspberry/log
POLL_PWD = ../raspberry/poll
RS232_PWD = ../raspberry/rs232
IFACE_PWD = ../interface
INCLUDE = -I$(IFACE_PWD) -I$(POLL_PWD)/src -Isrc -I$(RS232_PWD)/src -I$(LOG_PWD)/src -I$(UTIL_PWD)/src
LIBS = -L. -lusbi2c -lrs232 -lpoll -llog -lutil

CFLAGS = -g -std=c++11 $(INCLUDE)
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
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) libutil.so
	$(MAKE) liblog.so
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so:
	$(MAKE) libpoll.so
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libusbi2c.so: $(OBJECTS)
	$(MAKE) librs232.so
	$(CC) -shared $^ -o $@

#
##
libutil.dll:
	$(MAKE) -C $(UTIL_PWD) $@
	cp $(UTIL_PWD)/$@ .

liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

libpoll.dll:
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
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
