BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/mfrc522.o

SPI_REP = ../../ctrl/raspberry/spi
CC = g++
MAKE = make
INTERFACE_PWD = ../../../ctrl/interface
SPI_PWD = ../../../ctrl/raspberry/spi
INCLUDE = -I$(INTERFACE_PWD)/src -Isrc -I$(SPI_REP)/src
LIBS = -L. -lspidevice -lspi

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all: test_rfid

clean:
	rm $(BIN_PWD)/*.o libspi.so libspidevice.so test_rfid

test_rfid: $(BIN_PWD)/test_rfid.o libspidevice.so libraspispi.so
	$(CC) -o $@ $< $(LDFLAGS)

$(BIN_PWD)/test_rfid.o: test/test_rfid.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libraspispi.so:
	$(MAKE) -C $(SPI_REP) $@
	ln -s $(SPI_REP)/$@

libspidevice.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
