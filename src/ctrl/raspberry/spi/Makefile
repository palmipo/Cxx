BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/spi.o \
	$(BIN_PWD)/spiexception.o

CC = g++
INCLUDE = -I../../interface -Isrc
LIBS =

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libspi.so

clean:
	rm $(BIN_PWD)/*.o libspi.so

libspi.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/spi.o: src/spi.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_PWD)/spiexception.o: src/spiexception.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
