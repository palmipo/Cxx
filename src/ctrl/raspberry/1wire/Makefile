OBJECTS = \
	bin/onewire.o \
	bin/onewirerom.o

CC = g++
INCLUDE = -I../../.. -I../../interface -I../i2c/src -Isrc
LIBS =

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libonewire.so

clean:
	rm -f bin/*.o libonewire.so libi2c.so

libonewire.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libi2c.so:
	$(MAKE) -C ../i2c/ $@
	ln -s ../i2c/$@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
