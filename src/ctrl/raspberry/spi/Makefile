OBJECTS = \
	bin/spi.o \
	bin/spiexception.o

CC = g++
INCLUDE = -I../../interface -Isrc
LIBS =

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libspi.so

clean:
	rm bin/*.o libspi.so

libspi.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/spi.o: src/spi.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

bin/spiexception.o: src/spiexception.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
