BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hc_sr04.o

POLL_PWD = ../../../ctrl/raspberry/poll
UTIL_PWD = ../../../util
LOG_PWD = ../../../ctrl/raspberry/log
GPIO_PWD = ../../../ctrl/raspberry/gpio
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(POLL_PWD)/src -I$(LOG_PWD)/src -I$(GPIO_PWD)/src -I$(UTIL_PWD)/src
LIBS = -L. -llog -lgpio -lpoll -lutil

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS) -lpthread

all:

#
#
clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(GPIO_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so

#
#
telemetre: $(BIN_PWD)/test_telemetre.o
	$(MAKE) liblog.so
	$(MAKE) libutil.so
	$(MAKE) libpoll.so
	$(MAKE) libgpio.so
	$(MAKE) libhcsr04.so
	$(CC) -o $@ $^ $(LDFLAGS) -lhcsr04

$(BIN_PWD)/test_telemetre.o: test/test_telemetre.cpp
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
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

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
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

