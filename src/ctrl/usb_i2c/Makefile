BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/usb_i2c.o

LOG_PWD = ../raspberry/log
POLL_PWD = ../raspberry/poll
RS232_PWD = ../raspberry/rs232
CC = g++
INCLUDE = -I../.. -I../interface -I$(POLL_PWD)/src -Isrc -I$(RS232_PWD)/src -I$(LOG_PWD)
LIBS = -L. -lusbi2c -lrs232 -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libusbi2c.so

clean:
	rm -f $(BIN_PWD)/*.o *.so usbi2c

libusbi2c.so: $(OBJECTS)
	$(MAKE) librs232.so
	$(CC) -shared $^ -o $@


#
##
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

#
##
libpoll.so:
	$(MAKE) liblog.so
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so:
	$(MAKE) libpoll.so
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

usbi2c: $(BIN_PWD)/main.o
	$(MAKE) librs232.so
	$(MAKE) libusbi2c.so
	$(CC) $< -o $@ $(LDFLAGS)

$(BIN_PWD)/main.o: test/main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
