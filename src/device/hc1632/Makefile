BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hc1632.o

UTIL_REP = ../../util
LOG_REP = ../../ctrl/raspberry/log
POLL_REP = ../../ctrl/raspberry/poll
GPIO_REP = ../../ctrl/raspberry/gpio
AR = ar
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_REP)/src -I$(LOG_REP)/src -I$(POLL_REP)/src -I$(GPIO_REP)/src -Isrc -Ibadminton
LIBS = -L. -lutil -lgpio -lpoll -llog -lhc1632 -lm

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(GPIO_REP) $@
	$(MAKE) -C $(POLL_REP) $@
	$(MAKE) -C $(LOG_REP) $@
	rm $(BIN_PWD)/*.o *.so bad

bad: $(BIN_PWD)/badminton.o $(BIN_PWD)/badmintonfactory.o
	$(MAKE) libutil.so
	$(MAKE) libgpio.so
	$(MAKE) libpoll.so
	$(MAKE) liblog.so
	$(MAKE) libhc1632.so
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread

$(BIN_PWD)/badminton.o: badminton/badminton.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_PWD)/badmintonfactory.o: badminton/badmintonfactory.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libutil.so:
	$(MAKE) -C $(UTIL_REP) $@
	ln -s $(UTIL_REP)/$@

libgpio.so:
	$(MAKE) -C $(GPIO_REP) $@
	ln -s $(GPIO_REP)/$@

libpoll.so:
	$(MAKE) -C $(POLL_REP) $@
	ln -s $(POLL_REP)/$@

liblog.so:
	$(MAKE) -C $(LOG_REP) $@
	ln -s $(LOG_REP)/$@

libhc1632.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
