OBJECTS = \
	bin/hc_sr04.o

POLL_PWD = ../../../ctrl/raspberry/factory
LOG_PWD = ../../../ctrl/raspberry/log
GPIO_PWD = ../../../ctrl/raspberry/gpio
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(POLL_PWD)/src -I$(LOG_PWD)/src -I$(GPIO_PWD)/src
LIBS = -L. -llog -lgpio -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS) -lpthread

all:

#
#
clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(GPIO_PWD) $@
	rm -f bin/*.o *.so

#
#
telemetre: bin/test_telemetre.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libgpio.so
	$(MAKE) libhcsr04.so
	$(CC) -o $@ $^ $(LDFLAGS) -lhcsr04

bin/test_telemetre.o: test/test_telemetre.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
libgpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

#
#
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

#
#
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

#
#
libhcsr04.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

