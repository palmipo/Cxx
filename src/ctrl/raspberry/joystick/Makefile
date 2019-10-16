OBJECTS = \
	bin/joystick.o \
	bin/forcefeedback.o

LOG_PWD = ../log
POLL_PWD = ../factory
CC = g++
MAKE = make
INCLUDE = -I$(LOG_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -ljoystick -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

clean:
	rm bin/*.o *.so test_joystick

test_joystick: bin/test_joystick.o libjoystick.so
	$(CC) -o $@ $< $(LDFLAGS)

bin/test_joystick.o: test/test_joystick.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libjoystick.so: $(OBJECTS)
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(CC) -shared $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
