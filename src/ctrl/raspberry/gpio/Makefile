OBJECTS = \
	bin/gpio.o \
	bin/gpiofifo.o \
	bin/gpioevent.o \
	bin/gpiofactory.o

MAKE = make
CC = g++
POLL_PWD = ../poll
INCLUDE = -I$(POLL_PWD)/src -I../log/src -Isrc
LIBS = -L. -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C ../log $@
	$(MAKE) -C $(POLL_PWD) $@
	rm -f bin/*.o *.so *.dll out

out: bin/out.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libgpio.so
	$(CC) -o $@ $< -L. $(LDFLAGS) -lgpio

bin/out.o: test/out.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libgpio.so: $(OBJECTS)
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(CC) -shared $^ -o $@

# GLOBAL
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
