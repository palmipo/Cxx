BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/mfrc522.o

CC = g++
MAKE = make
INTERFACE_PWD = ../../../ctrl/interface
UTIL_PWD = ../../../util
SPI_PWD = ../../../ctrl/raspberry/spi
POLL_PWD = ../../../ctrl/raspberry/poll
GPIO_PWD = ../../../ctrl/raspberry/gpio
LOG_PWD = ../../../ctrl/raspberry/log
PIA_PWD = ../../pia
INCLUDE = -Isrc -I$(UTIL_PWD)/src -I$(INTERFACE_PWD)/src -I$(SPI_PWD)/src -I$(PIA_PWD)/src -I$(GPIO_PWD)/src -I$(POLL_PWD)/src -I$(LOG_PWD)/src
LIBS = -L. -lspidevice -lraspispi -lpia -lraspigpio -lpoll -llog

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all: test_rfid

clean:
	rm $(BIN_PWD)/*.o libspidevice.so libraspispi.so test_rfid

test_rfid: $(BIN_PWD)/test_rfid.o libspidevice.so libraspispi.so libraspigpio.so libpia.so libpoll.so liblog.so
	$(CC) -o $@ $< $(LDFLAGS)

$(BIN_PWD)/test_rfid.o: test/test_rfid.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libraspispi.so:
	$(MAKE) -C $(SPI_PWD) $@
	ln -s $(SPI_PWD)/$@

libraspigpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libpia.so:
	$(MAKE) -C $(PIA_PWD) $@
	ln -s $(PIA_PWD)/$@

libspidevice.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
