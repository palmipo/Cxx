OBJECTS = \
	bin/rc522.o

SPI_REP = ../../ctrl/raspberry/spi
CC = g++
MAKE = make
INCLUDE = -I.. -I../.. -I../../ctrl/interface -I../../ctrl/raspberry/factory/src -Isrc -I$(SPI_REP)/src
LIBS = -L. -lspidevice -lspi

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: test_rfid

clean:
	rm bin/*.o libspi.so libspidevice.so test_rfid

test_rfid: bin/test_rfid.o libspidevice.so
	$(CC) -o $@ $< $(LDFLAGS)

bin/test_rfid.o: test/test_rfid.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libspi.so:
	$(MAKE) -C $(SPI_REP) $@
	ln -s $(SPI_REP)/$@

libspidevice.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

bin/rc522.o: src/rc522.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
