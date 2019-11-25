BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/gpio.o \
	$(BIN_PWD)/gpiofifo.o \
	$(BIN_PWD)/gpioevent.o \
	$(BIN_PWD)/gpiofactory.o

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
	rm -f $(BIN_PWD)/*.o *.so *.dll out

out: $(BIN_PWD)/out.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libgpio.so
	$(CC) -o $@ $< -L. $(LDFLAGS) -lgpio

$(BIN_PWD)/out.o: test/out.cpp
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
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
