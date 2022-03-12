BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hc1632.o

UTIL_REP = ../../util
POLL_REP = ../../ctrl/raspberry/poll
GPIO_REP = ../../ctrl/raspberry/gpio
PIA_REP = ../pia
AR = ar
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_REP)/src -I$(PIA_REP)/src -I$(POLL_REP)/src -I$(GPIO_REP)/src -Isrc -Ibadminton
LIBS = -L. -lpia -lraspigpio -lpoll -lhc1632

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(GPIO_REP) $@
	$(MAKE) -C $(POLL_REP) $@
	rm $(BIN_PWD)/*.o *.so bad

test_aff: $(BIN_PWD)/test.o libpoll.so libraspigpio.so libpia.so libhc1632.so
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/test.o: test/test.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

bad: $(BIN_PWD)/badminton.o $(BIN_PWD)/badmintonfactory.o libraspigpio.so libpoll.so libraspipia.so libhc1632.so
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread

$(BIN_PWD)/badminton.o: badminton/badminton.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_PWD)/badmintonfactory.o: badminton/badmintonfactory.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libpia.so:
	$(MAKE) -C $(PIA_REP) $@
	ln -s $(PIA_REP)/$@

libraspigpio.so:
	$(MAKE) -C $(GPIO_REP) $@
	ln -s $(GPIO_REP)/$@

libpoll.so:
	$(MAKE) -C $(POLL_REP) $@
	ln -s $(POLL_REP)/$@

libhc1632.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
